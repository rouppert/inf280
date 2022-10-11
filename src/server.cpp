//
//  server.cpp
//  TP C++
//  Eric Lecolinet - Telecom ParisTech - 2016.
//

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "server.h"
using namespace cppu;
using namespace std;

const int PORT = 3331;

GenericTable* table = new GenericTable();

string parseRequest(const string& request) {
  string command;
  istringstream iss(request);
  int i = 0;
  string cmd;
  string arg;
  while (i < 2) {
    string word;
    iss >> word;
    if (i==0) {
      if((word == "find") | (word == "play")) {
        cmd = word;
      }
      else {
        cerr << "Unknown command";
      }
    }
    if (i==1) {
      arg = word;
    }
    i++;
  }

  if (cmd=="find") {
    if (table -> searchMultimedia(arg)!=nullptr) {
      command = "command is find" + table -> searchMultimedia (arg) -> displayParam(cout);
    }
    else {
      cerr << "couldn't find element";
    }  
  }

  if (cmd=="play") {
    if (table -> searchMultimedia(arg)!=nullptr) {
      table -> searchMultimedia (arg) -> play();
      command = "Object succesfully played";
    }
    else {
      cerr << "couldn't find element";
    } 
  }
  return command;
}



class MyBase {
public:
  /* Cette méthode est appelée chaque fois qu'il y a une requête à traiter.
   * Ca doit etre une methode de la classe qui gere les données, afin qu'elle
   * puisse y accéder.
   *
   * Arguments:
   * - 'request' contient la requête
   * - 'response' sert à indiquer la réponse qui sera renvoyée au client
   * - si la fonction renvoie false la connexion est close.
   *
   * Cette fonction peut etre appelée en parallele par plusieurs threads (il y a
   * un thread par client).
   *
   * Pour eviter les problemes de concurrence on peut créer un verrou en creant
   * une variable Lock **dans la pile** qui doit etre en mode WRITE (2e argument = true)
   * si la fonction modifie les donnees.
   */
  bool processRequest(TCPConnection& cnx, const string& request, string& response)
  {
    cerr << "\nRequest: '" << request << "'" << endl;

    // 1) pour decouper la requête:
    // on peut par exemple utiliser stringstream et getline()
    
    
    // 2) faire le traitement:
    // - si le traitement modifie les donnees inclure: TCPLock lock(cnx, true);
    // - sinon juste: TCPLock lock(cnx);


    // 3) retourner la reponse au client:
    // - pour l'instant ca retourne juste OK suivi de la requête
    // - pour retourner quelque chose de plus utile on peut appeler la methode print()
    //   des objets ou des groupes en lui passant en argument un stringstream
    // - attention, la requête NE DOIT PAS contenir les caractères \n ou \r car
    //   ils servent à délimiter les messages entre le serveur et le client
    
    response = "OK: " + parseRequest(request);
    cerr << "response: " << response << endl;
    
    // renvoyer false si on veut clore la connexion avec le client
    return true;
  }
};


int main(int argc, char* argv[])
{
  // cree le TCPServer
  shared_ptr<TCPServer> server(new TCPServer());
  
  // cree l'objet qui gère les données
  shared_ptr<MyBase> base(new MyBase());

  // cree une table d'objet multimedia d'après la liste des contenus dans la base de données.
  fstream f;
  f.open("multimedia/Database.txt");
  if(!f) {
    cerr << "Can't open file " << "database.txt" << endl;
  }
  while(f) {
    table -> createObject(f);
  }
  f.close();

  // le serveur appelera cette méthode chaque fois qu'il y a une requête
  server->setCallback(*base, &MyBase::processRequest);

  // lance la boucle infinie du serveur
  cout << "Starting Server on port " << PORT << endl;
  int status = server->run(PORT);

  // en cas d'erreur
  if (status < 0) {
    cerr << "Could not start Server on port " << PORT << endl;
    return 1;
  }
  
  return 0;
}
