bin_PROGRAMS = guessnumber
pkgdata_DATA=ru_RU/LC_MESSAGES/guessnumber.mo

	@DX_RULES@

guessnumber.o: guessnumber.c

ru_RU/LC_MESSAGES/guessnumber.mo: ru.po
	mkdir -p `dirname $@`
	msgfmt $< -o $@

ru.po:	messages.pot
	msgmerge -U $@ $<

messages.pot: guessnumber.c guessnumber.pot
	xgettext -k_ -c $< -o messages.new.pot
	cp guessnumber.pot $@
	msgmerge -U $@ messages.new.pot

gitclean:
	git clean -df

allclean: gitclean
	rm -rf *.o ru_RU/LC_MESSAGES/*.mo *~
