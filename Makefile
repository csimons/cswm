include config.mk

SRC = client.c event.c main.c util.c view.c
OBJ = ${SRC:.c=.o}

all: options cswm

options:
	@echo cswm build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC	   = ${CC}"

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

${OBJ}: cswm.h config.mk

cswm: ${OBJ}
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}
	@strip $@

clean:
	@echo cleaning
	@rm -f cswm ${OBJ} cswm-${VERSION}.tar.gz

dist: clean
	@echo creating dist tarball
	@mkdir -p cswm-${VERSION}
	@cp -R LICENSE Makefile README config.*.h config.mk \
		cswm.1 cswm.h ${SRC} cswm-${VERSION}
	@tar -cf cswm-${VERSION}.tar cswm-${VERSION}
	@gzip cswm-${VERSION}.tar
	@rm -rf cswm-${VERSION}

install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f cswm ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/cswm
	@echo installing manual page to ${DESTDIR}${MANPREFIX}/man1
	@mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@sed 's/VERSION/${VERSION}/g' < cswm.1 > ${DESTDIR}${MANPREFIX}/man1/cswm.1
	@chmod 644 ${DESTDIR}${MANPREFIX}/man1/cswm.1

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/cswm
	@echo removing manual page from ${DESTDIR}${MANPREFIX}/man1
	@rm -f ${DESTDIR}${MANPREFIX}/man1/cswm.1

.PHONY: all options clean dist install uninstall
