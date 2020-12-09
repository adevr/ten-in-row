arbitro:
	gcc -o moderator/moderator constants/constants.h helpers/helpers.c models/Communication/Communication.c moderator/Moderator.c moderator/models/Application/Game.c moderator/models/Client/Client.c moderator/main.c

cliente:
	gcc -o client/client constants/constants.h helpers/helpers.c  models/Communication/Communication.c client/Client.c client/main.c

jogo:
	gcc -o application/game constants/constants.h helpers/helpers.c  models/Communication/Communication.c application/Game.c application/main.c

all: arbitro cliente jogo
	gcc -o teninrow constants/constants.h main.c

clean:
	rm application/game
	rm client/client
	rm moderator/moderator
	rm teninrow