#include <glib.h>
#include <stdio.h>
#include "config.h"

gint compare_func(gconstpointer a, gconstpointer b)
{
	if (a < b)
		return -1;
	else if (a == b)
	 	return 0;
	else
		return 1;
}

int main()
{
	FILE *fp;
	if (!(fp = fopen("input.txt", "r")))
	{
		printf("Cannot open input.txt file.\n");
		return 1;
	}
	char buff[80];
	GHashTable *hash = g_hash_table_new(g_str_hash, g_int_equal);
	while(!feof(fp))
	{
		if (fgets(buff, 80, fp))
		{
			int last = strlen(buff) - 1;
			if (buff[last] == '\n')
				buff[last] = '\0';
			gchar **words = g_strsplit((gchar *)buff, " ", -1);
			for (gchar **word = words; *word; word++)
			{
				if (!strcmp((char*)*word,""))
					continue;
				gpointer num = g_hash_table_lookup(hash, *word);
				if (!num)
					g_hash_table_insert(hash, *word, GINT_TO_POINTER(1));
				else
					g_hash_table_insert(hash, *word, GINT_TO_POINTER(GPOINTER_TO_INT(num) + 1));
			}
			g_strfreev(words);
		}
	}

	GList *list = g_hash_table_get_values(hash), *node;
	list = g_list_sort(list, compare_func);
	for (node = list; node; node = node->next)
		printf("%d\n", GPOINTER_TO_INT(node->data));

	g_list_free(list);
	g_hash_table_destroy(hash);

	return 0;
}
