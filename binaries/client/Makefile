VPATH=../../game ../../linux ../../qcommon ../../server ../../client	

quake2_SRC:=cl_cin.c cl_ents.c cl_fx.c cl_input.c cl_inv.c cl_main.c\
	    cl_parse.c cl_pred.c cl_tent.c cl_scrn.c cl_view.c cl_newfx.c\
	    console.c keys.c menu.c snd_dma.c snd_mem.c snd_mix.c qmenu.c\
	    m_flash.c\
	    cmd.c cmodel.c common.c crc.c cvar.c files.c md4.c net_chan.c\
	    sv_ccmds.c sv_ents.c sv_game.c sv_init.c sv_main.c sv_send.c\
	    sv_user.c sv_world.c \
	    q_shlinux.c vid_menu.c vid_so.c sys_linux.c glob.c net_udp.c\
	    q_shared.c pmove.c snd_openal.c mersennetwister.c le_util.c\
	    le_physics.c redblack.c cd_linux.c snd_linux.c 

quake2_OBJ:=$(quake2_SRC:.c=.o)
ALLSRC:=$(quake2_SRC)

.PHONY: default

default: quake2

TARGETS:=quake2

include ../make.inc

quake2: $(quake2_OBJ)
	gcc -g -o $@ $^ -lm -lz -ldl

-include .depends/*.d