CC=gcc
flags=-lm -O3
dev_flags=-lm -g -fsanitize=address -Wall
lib=libs.c
network=net
battery=bat
brightness=brightness
# player=player
builddir=build
bluetooth=blue
volume=vol

devdir=build-dev

default:
	mkdir -p ${builddir}
	# ${CC} libs.c -c ${lib}  
	${CC}  battery.c ${lib} -o ${builddir}/${battery} ${flags}
	${CC} ${lib} brightness.c -o ${builddir}/${brightness} ${flags}
	${CC} ${lib} net.c -o ${builddir}/${network} ${flags}
	${CC} ${lib} bluetooth.c -o ${builddir}/${bluetooth} ${flags}
	${CC} ${lib} volume.c -o ${builddir}/${volume} ${flags}
	# ${CC} ${lib} player.c -o ${builddir}/${player} ${flags}

dev:
	mkdir -p ${devdir}
	# ${CC} libs.c -c ${lib}  
	${CC}  battery.c ${lib} -o ${devdir}/${battery} ${dev_flags}
	${CC} ${lib} brightness.c -o ${devdir}/${brightness} ${dev_flags}
	${CC} ${lib} net.c -o ${devdir}/${network} ${dev_flags}
	${CC} ${lib} bluetooth.c -o ${devdir}/${bluetooth} ${dev_flags}
	${CC} ${lib} volume.c -o ${devdir}/${volume} ${dev_flags}
