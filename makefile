GAME_NUMBER ?= 1

arbitro:
	gcc -o moderator/moderator -pthread constants/constants.h helpers/helpers.c models/Communication/Communication.c moderator/Moderator.c moderator/models/Application/Game.c moderator/models/Client/Client.c moderator/main.c

cliente:
	gcc -o client/client -pthread constants/constants.h helpers/helpers.c  models/Communication/Communication.c client/Client.c client/main.c

jogo:
	gcc -o application/g_$(GAME_NUMBER) -pthread constants/constants.h helpers/helpers.c  models/Communication/Communication.c application/Game.c application/main.c

all: arbitro cliente jogo
	gcc -o teninrow -pthread constants/constants.h main.c

clean:
	rm application/g_*
	rm client/client
	rm moderator/moderator
	rm teninrow