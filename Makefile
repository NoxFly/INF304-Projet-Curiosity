CC := clang -Wall
SRCDIR := ./src/
INCDIR := ./include/

PROGRAMMES := test_terrain test_robot robot_terrain curiosity curiosity-test test_generation_terrains

all: $(PROGRAMMES)
	rm -f *.o

######################################################################
#                       Règles de compilation                        #
######################################################################

%.o: $(SRCDIR)%.c
	$(CC) -c $<

test_terrain.o: $(SRCDIR)test_terrain.c $(INCDIR)terrain.h

test_robot.o: $(SRCDIR)test_robot.c $(INCDIR)robot.h

robot_terrain.o: $(SRCDIR)robot_terrain.c $(INCDIR)terrain.h $(INCDIR)robot.h

robot.o: $(SRCDIR)robot.c $(INCDIR)robot.h

terrain.o: $(SRCDIR)terrain.c $(INCDIR)terrain.h

environnement.o: $(SRCDIR)environnement.c $(INCDIR)environnement.h $(INCDIR)robot.h $(INCDIR)terrain.h

programme.o: $(SRCDIR)programme.c $(INCDIR)programme.h $(INCDIR)type_pile.h

interprete.o: $(SRCDIR)interprete.c $(INCDIR)interprete.h $(INCDIR)environnement.h \
	$(INCDIR)programme.h $(INCDIR)type_pile.h $(INCDIR)robot.h $(INCDIR)terrain.h

interprete%.o: $(SRCDIR)interprete%.c $(INCDIR)interprete.h $(INCDIR)environnement.h \
	$(INCDIR)programme.h $(INCDIR)type_pile.h $(INCDIR)robot.h $(INCDIR)terrain.h

type_pile.o: $(SRCDIR)type_pile.c $(INCDIR)type_pile.h

curiosity.o: $(SRCDIR)curiosity.c $(INCDIR)environnement.h $(INCDIR)programme.h \
	$(INCDIR)interprete.h $(INCDIR)robot.h $(INCDIR)terrain.h $(INCDIR)type_pile.h

curiosity-test.o: $(SRCDIR)curiosity-test.c $(INCDIR)environnement.h $(INCDIR)programme.h \
	$(INCDIR)interprete.h $(INCDIR)robot.h $(INCDIR)terrain.h $(INCDIR)type_pile.h

generation_terrains.o: $(SRCDIR)generation_terrains.c $(INCDIR)generation_terrains.h

test_generation_terrains.o: $(SRCDIR)test_generation_terrains.c $(INCDIR)generation_terrains.h $(INCDIR)terrain.h

######################################################################
#                       Règles d'édition de liens                    #
######################################################################

test_programme: environnement.o robot.o test_programme.o interprete.o
	$(CC) $^ -o $@

test_terrain: test_terrain.o terrain.o
	$(CC) $^ -o $@

test_robot: test_robot.o robot.o
	$(CC) $^ -o $@

robot_terrain: robot_terrain.o terrain.o robot.o
	$(CC) $^ -o $@

curiosity: curiosity.o environnement.o programme.o interprete.o \
	robot.o terrain.o type_pile.o
	$(CC) $^ -o $@

curiosity-test: curiosity-test.o environnement.o programme.o interprete.o \
	robot.o terrain.o type_pile.o
	$(CC) $^ -o $@

curiosity-test%: curiosity-test.o environnement.o programme.o interprete%.o \
	robot.o terrain.o type_pile.o
	$(CC) $^ -o $@

test_generation_terrains: test_generation_terrains.o terrain.o generation_terrains.o
	$(CC) $^ -o $@

clean:
	rm -f $(PROGRAMMES) *.o

cleanO:
	rm -f *.o