# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# Copyright 2001-2004, ps2dev - http://www.ps2dev.org
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.

EE_BIN = PONG.ELF
EE_OBJS = Main.o GameRNG.o ColourRGBA.o GameClock.o GameMath.o GameObject.o Global_Flags.o PlayerController.o RenderableComponent.o RenderEngine.o Timer.o GameEngine.o PlayerScore.o PongBall.o PadHandler.o
EE_LDFLAGS = -L$(PS2SDK)/ports/lib/ -L$(PS2DEV)/gsKit/lib 
EE_LIBS = -ldraw -lgraph -lmath3d -lpacket -ldma -lSDL2 -lSDL2_ttf -lSDL2main -lSDL2_image -lSDL2_mixer -lSDL2_test  -lfreetype -lpadx -lgskit -lz -lcdvd -lm -lps2ip -lnetman -ldmakit -lpng -lmtap -Lmodules/ds34usb/ee/ -lpatches -lfileXio -lpad -ldebug -lmath3d -ljpeg -lfreetype -lgskit_toolkit -lgskit -ldmakit -lpng -lz -lmc -laudsrv -lelf-loader -laudsrv -lc -lps2_drivers
EE_INCS :=  -I$(PS2SDK)/ee/include -I$(PS2SDK)/common/include -I. $(EE_INCS) -I$(PS2SDK)/ports/include/SDL2 -I$(PS2SDK)/ports/include
ISO_TGT=pong.iso
EE_CXXFLAGS = -fpermissive

RES_INCLUDES = USN_STENCIL.TTF
all: $(ISO_TGT)
	$(EE_STRIP) --strip-all $(EE_BIN)
$(ISO_TGT): $(EE_BIN)
	mkisofs -l -o $(ISO_TGT) $(EE_BIN) SYSTEM.CNF $(RES_INCLUDES)

clean:
	rm -f $(EE_BIN) $(EE_OBJS)

run: $(EE_BIN)
	ps2client execee host:$(EE_BIN)

reset:
	ps2client reset

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal_cpp

