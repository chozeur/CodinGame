#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

typedef struct s_data{
	int		tablen;
	int		filen;
	char	**extension;
	char	**mimetype;
	char	**file;
}	t_data;


int		min(int a, int b);
char	*get_ext(char *file_name);
char	*answer(t_data *data, int i);
char	*strlow(char *str);

int	main()
{
	int N, Q;
	t_data	data;

	scanf("%d%d", &N, &Q);
	fprintf(stderr, "N = %d\tN = %d\n", N, Q);
	data.tablen = N;
	data.filen = Q;
	data.extension = malloc(sizeof(char *) * data.tablen);
	data.mimetype = malloc(sizeof(char *) *data. tablen);
	data.file = malloc(sizeof(char *) * data.filen);
	for (int i = 0; i < data.tablen; i++) {
		data.extension[i] = malloc(4096);
		data.mimetype[i] = malloc(4096);
		scanf("%s%s", data.extension[i], data.mimetype[i]); fgetc(stdin);
		fprintf(stderr, "ext : %s\tmime : %s\n", data.extension[i], data.mimetype[i]);
	}
	for (int i = 0; i < data.filen; i++) {
		data.file[i] = malloc(4096);
		scanf("%[^\n]", data.file[i]); fgetc(stdin);
		fprintf(stderr, "file : %s\n", data.file[i]);
		printf("%s\n", answer(&data, i));
	}
	return (0);
}

char	*get_ext(char *file_name)
{
	int		i, j;
	char	*res, *tmp;

	i = strlen(file_name) - 1;
	res = malloc(4096);
	tmp = malloc(4096);
	j = 0;
	while (i >= 0)
	{
		if (file_name[i] == '.')
			break ;
		tmp[j++] = file_name[i];
		i--;
	}
	tmp[j] = '\0';
	i = strlen(tmp) - 1;
	j = 0;
	while (i >= 0)
		res[j++] = tmp[i--];
	free(tmp);
	return (res);
}

char	*answer(t_data *data, int i)
{
	for (int n = 0; n < data->tablen; n++){
		if (!strncmp(strlow(data->extension[n]), strlow(get_ext(data->file[i])), min(strlen(data->extension[n]), strlen(data->file[i]))))
			return (data->mimetype[n]);
	}
	return ("UNKNOWN");
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

char	*strlow(char *str)
{
	for (int i = 0; str[i]; i++){
		str[i] = (char)tolower(str[i]);
	}
	return (str);
}
