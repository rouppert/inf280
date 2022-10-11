##########################################
#
#  Exemple de Makefile
#  Eric Lecolinet - Reda Dehak - Telecom ParisTech 2015
#  INF224 - TP C++ - http://www.telecom-paristech.fr/~elc/inf224
#
##########################################

#
# Nom du programme
#
CLIENT=client
SERVER=server
CLISERV=cliserv
PROG=main

#
# Fichiers sources (NE PAS METTRE les .h ni les .o seulement les .cpp)
#

SRCDIR = src/
JAVA_SOURCES = Client.java  mainWindow.java
PROG_SOURCES = film.cpp genericTable.cpp group.cpp main.cpp multimedia.cpp photo.cpp video.cpp
CLIENT_SOURCES=client.cpp socket.cpp 
SERVER_SOURCES=server.cpp tcpserver.cpp socket.cpp film.cpp group.cpp genericTable.cpp multimedia.cpp photo.cpp video.cpp
CLISERV_SOURCES=client.cpp server.cpp tcpserver.cpp socket.cpp film.cpp group.cpp

PROG_SOURCES_FILES = $(addprefix $(SRCDIR), ${PROG_SOURCES})
CLIENT_SOURCES_FILES = $(addprefix $(SRCDIR), ${CLIENT_SOURCES})
SERVER_SOURCES_FILES = $(addprefix $(SRCDIR), ${SERVER_SOURCES})
CLISERV_SOURCES_FILES = $(addprefix $(SRCDIR), ${CLISERV_SOURCES})
JAVA_SOURCES_FILES = $(addprefix ${SRCDIR}tele_interface/, ${JAVA_SOURCES})

#
# Fichiers OBJECTS (ne pas modifier sauf si l'extension n'est pas .cpp)
#

OBJDIR = build/
PROG_OBJECTS = $(subst cpp,o ,${PROG_SOURCES})
PROG_OBJECTS_FILES = $(addprefix $(OBJDIR), ${PROG_OBJECTS})
CLIENT_OBJECTS = $(subst cpp,o ,${CLIENT_SOURCES})
CLIENT_OBJECTS_FILES = $(addprefix $(OBJDIR), ${CLIENT_OBJECTS})
SERVER_OBJECTS = $(subst cpp,o ,${SERVER_SOURCES})
SERVER_OBJECTS_FILES = $(addprefix $(OBJDIR), ${SERVER_OBJECTS})
JAVA_CLASSES = $(subst java,class ,${JAVA_SOURCES})
JAVA_CLASSES_FILES = $(addprefix ${OBJDIR}tele_interface/, ${JAVA_CLASSES})

#
# Compilateur C++
#
CXX = c++
JFLAGS = -g
JC = javac

#
# Options du compilateur C++
#   -g pour debugger, -O optimise, -Wall affiche les erreurs, -I pour les headers
#   -std=c++11 pour C++11
# Exemple: CXXFLAGS= -std=c++11 -Wall -O -I/usr/local/qt/include
#
CXXFLAGS = -std=c++11 -Wall -g -I /home/pascal/Programmation/INF224/include

#
# Options de l'editeur de liens
#
LDFLAGS = 

#
# Librairies a utiliser
# Exemple: LDLIBS = -L/usr/local/qt/lib -lqt
#
LDLIBS = -lpthread


##########################################
#
# Regles de construction/destruction des .o et de l'executable
# depend-${PROG} sera un fichier contenant les dependances
#
 
all: ${CLIENT} ${SERVER} ${PROG}
	$(JC) $(JFLAGS) ${JAVA_SOURCES_FILES} -d ${OBJDIR}

run-${SERVER}: ${SERVER}
	./${SERVER}

run-${CLIENT}: ${CLIENT}
	./${CLIENT}

run-interface:
	/usr/bin/env /usr/lib/jvm/java-11-openjdk-amd64/bin/java -cp /home/pascal/Programmation/INF224/build tele_interface.mainWindow 

${PROG}: ${PROG_OBJECTS_FILES}
	${CXX} ${CXXFLAGS} ${LDFLAGS} ${LDLIBS} ${PROG_OBJECTS_FILES} -o $@

${CLIENT}: ${CLIENT_OBJECTS_FILES}
	${CXX} ${CXXFLAGS} ${LDFLAGS} ${LDLIBS} ${CLIENT_OBJECTS_FILES} -o $@

${SERVER}: ${SERVER_OBJECTS_FILES}
	${CXX} ${CXXFLAGS} ${LDFLAGS} ${LDLIBS} ${SERVER_OBJECTS_FILES} -o $@

clean-c:
	rm -f ${CLIENT_OBJECTS_FILES} ${SERVER_OBJECTS_FILES} ${PROG_OBJECTS_FILES}

clean-java:
	rm -f ${OBJDIR}/tele_interface/*.class

clean-all: clean-c clean-java
	-@$(RM) ${CLIENT} ${SERVER} ${PROG}

build/%.o: src/%.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) $< -o $@

${OBJDIR}/%.class: ${SRCDIR}/%.java
	$(JC) $(JFLAGS) $< -d ${OBJDIR}


###########################################
#
# Regles implicites
#

.SUFFIXES: .cpp .cxx .c

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

