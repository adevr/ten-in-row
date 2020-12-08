arbitro:
	gcc -o moderator/moderator models/Communication/Communication.c helpers/helpers.c moderator/Moderator.c moderator/models/Application/Game.c moderator/models/Client/Client.c moderator/main.c

cliente:
	gcc -o client/client models/Communication/Communication.c helpers/helpers.c client/Client.c client/main.c

jogo:
	gcc -o application/game models/Communication/Communication.c application/Game.c application/main.c

all: arbitro cliente jogo
	gcc -o teninrow main.c


clean:
	rm application/game
	rm client/client
	rm moderator/moderator
	rm teninrow