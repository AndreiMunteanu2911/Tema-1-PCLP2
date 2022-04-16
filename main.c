#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "structs.h"

int get_byte_length(void** arr, int* len)
{
	int nr = 0;
	for (int i = 0; i < *len; i++)
	{
		head* p = (head*)malloc(sizeof(head));
		memcpy(p, (char*)*arr + nr, sizeof(head));
		nr = nr + p->len + sizeof(head);
	}
	return nr;
}

int add_last(void** arr, int* len, data_structure* data)
{
	int byte_count = get_byte_length(arr, len);
	if (*arr == NULL)
	{
		*arr = (char*)malloc(byte_count + data->header->len + sizeof(head));
	}
	else
	{
		*arr = (char*)realloc(*arr, byte_count + data->header->len + sizeof(head));
	}
	if (*arr == NULL)
	{
		return -1;
	}
	*arr = (char*)*arr;
	char* p = *arr;
	data->header = (char*)data->header;
	memcpy((char*)*arr + byte_count, data->header, sizeof(head));
	memcpy((char*)*arr + byte_count + sizeof(head), data->data, data->header->len);
	*len = *len + 1;
	return 0;
}

int add_at(void** arr, int* len, data_structure* data, int index)
{
	if (index < 0)
	{
		return -1;
	}
	if (index > *len)
	{
		add_last(arr, len, data);
		return 0;
	}
	int byte_count = get_byte_length(arr, len);
	char* p = *arr;
	int current = 0;
	for (int i = 0; i < index; i++)
	{
		head* header = (head*)malloc(sizeof(head));
		memcpy(header, (char*)p + current, sizeof(head));
		current = current + sizeof(head);
		current = current + header->len;
	}
	int index_start = current;
	int nr_to_cpy = byte_count - index_start;
	*arr = (char*)realloc(*arr, byte_count + data->header->len + sizeof(head));
	memcpy((char*)*arr + index_start + sizeof(head) + data->header->len, (char*)*arr + index_start, nr_to_cpy);
	memcpy((char*)*arr + index_start, data->header, sizeof(head));
	memcpy((char*)*arr + index_start + sizeof(head), data->data, data->header->len);
	*len = *len + 1;
	return 0;
}

void find(void* data_block, int len, int index)
{
	if (data_block == NULL)
	{
		return;
	}
	if (index < 0 || index >= len)
	{
		return;
	}
	int byte_count = get_byte_length(&data_block, &len);
	char* p = data_block;
	int current = 0;
	for (int i = 0; i < index; i++)
	{
		head* header = (head*)malloc(sizeof(head));
		memcpy(header, (char*)p + current, sizeof(head));
		current = current + sizeof(head);
		current = current + header->len;
	}
	head* header = (head*)malloc(sizeof(head));
	memcpy(header, (char*)data_block + current, sizeof(head));
	current = current + sizeof(head);
	printf("Tipul %c\n", header->type);
	while (p[current] != '\0')
	{
		printf("%c", p[current]);
		current++;
	}
	current++;
	printf(" pentru ");
	int nr_start = current;
	if (header->type == '1')
	{
		current = current + 2;
	}
	if (header->type == '2')
	{
		current = current + 6;
	}
	if (header->type == '3')
	{
		current = current + 8;
	}
	while (p[current] != '\0')
	{
		printf("%c", p[current]);
		current++;
	}
	printf("\n");
	if (header->type == '1')
	{
		int8_t nr1 = 0;
		memcpy(&nr1, &p[nr_start], 1);
		int8_t nr2 = 0;
		memcpy(&nr2, &p[nr_start] + 1, 1);
		printf("%"PRId8, nr1);
		printf("\n");
		printf("%"PRId8, nr2);
	}
	if (header->type == '2')
	{
		int16_t nr1 = 0;
		memcpy(&nr1, &p[nr_start], 2);
		int32_t nr2 = 0;
		memcpy(&nr2, &p[nr_start] + 2, 4);
		printf("%"PRId16, nr1);
		printf("\n");
		printf("%"PRId32, nr2);
	}
	if (header->type == '3')
	{
		int32_t nr1 = 0;
		memcpy(&nr1, &p[nr_start], 4);
		int32_t nr2 = 0;
		memcpy(&nr2, &p[nr_start] + 4, 4);
		printf("%"PRId32, nr1);
		printf("\n");
		printf("%"PRId32, nr2);
	}
	current++;
	printf("\n\n");
	byte_count = byte_count - sizeof(head) - header->len;
}

int delete_at(void** arr, int* len, int index)
{
	if (index < 0 || index >= len)
	{
		return -1;
	}
	int byte_count = get_byte_length(arr, len);
	char* p = *arr;
	int current = 0;
	for (int i = 0; i < index; i++)
	{
		head* header = (head*)malloc(sizeof(head));
		memcpy(header, (char*)p + current, sizeof(head));
		current = current + sizeof(head);
		while (p[current] != '\0')
		{
			current++;
		}
		current++;
		if (header->type == '1')
		{
			current = current + 2;
		}
		if (header->type == '2')
		{
			current = current + 6;
		}
		if (header->type == '3')
		{
			current = current + 8;
		}
		while (p[current] != '\0')
		{
			current++;
		}
		current++;
	}
	int index_start = current;
	head* header = (head*)malloc(sizeof(head));
	memcpy(header, (char*)p + current, sizeof(head));
	int len_rem = header->len;
	int nr_to_cpy = byte_count - sizeof(head) - len_rem - index_start;
	memcpy((char*)*arr + index_start, (char*)*arr + index_start + sizeof(head) + len_rem, nr_to_cpy);
	*len = *len - 1;
	return 0;
}

void print(void* arr, int len)
{
	if (arr == NULL)
	{
		return;
	}
	int byte_count = get_byte_length(&arr, &len);
	char* p = arr;
	int current = 0;
	while (byte_count > 0)
	{
		head* header = (head*)malloc(sizeof(head));
		memcpy(header, (char*)arr + current, sizeof(head));
		char* p = arr;
		current = current + sizeof(head);
		printf("Tipul %c\n", header->type);
		while (p[current] != '\0')
		{
			printf("%c", p[current]);
			current++;
		}
		current++;
		printf(" pentru ");
		int nr_start = current;
		if (header->type == '1')
		{
			current = current + 2;
		}
		if (header->type == '2')
		{
			current = current + 6;
		}
		if (header->type == '3')
		{
			current = current + 8;
		}
		while (p[current] != '\0')
		{
			printf("%c", p[current]);
			current++;
		}
		printf("\n");
		if (header->type == '1')
		{
			int8_t nr1 = 0;
			memcpy(&nr1, &p[nr_start], 1);
			int8_t nr2 = 0;
			nr_start = nr_start + 1;
			memcpy(&nr2, &p[nr_start], 1);
			printf("%"PRId8, nr1);
			printf("\n");
			printf("%"PRId8, nr2);
		}
		if (header->type == '2')
		{
			int16_t nr1 = 0;
			memcpy(&nr1, &p[nr_start], 2);
			int32_t nr2 = 0;
			nr_start = nr_start + 2;
			memcpy(&nr2, &p[nr_start], 4);
			printf("%"PRId16, nr1);
			printf("\n");
			printf("%"PRId32, nr2);
		}
		if (header->type == '3')
		{
			int32_t nr1 = 0;
			memcpy(&nr1, &p[nr_start], 4);
			int32_t nr2 = 0;
			nr_start = nr_start + 4;
			memcpy(&nr2, &p[nr_start], 4);
			printf("%"PRId32, nr1);
			printf("\n");
			printf("%"PRId32, nr2);
		}
		current++;
		printf("\n\n");
		byte_count = byte_count - sizeof(head) - header->len;
	}
}

int main() {
	// the vector of bytes u have to work with
	// good luck :)
	void* arr = NULL;
	int len = 0;
	/*int8_t x = 5;
	printf("%"PRId8, x);*/
	while (0 == 0)
	{
		char command[500];
		char buffer[500];
		fscanf(stdin, "%s", &command);
		if ((strcmp("insert", command)) == 0)
		{
			// citire tip
			fscanf(stdin, "%s", &buffer);
			// alocare header
			head* header = (head*)malloc(sizeof(head));
			//strncpy(header->type, buffer, 1);
			header->type = buffer[0];
			// citire primul nume
			fscanf(stdin, "%s", &buffer);
			// alocare data_buffer
			char* data_buffer = (char*)malloc(strlen(buffer) + 1);
			int data_len = strlen(buffer) + 1;
			strcpy(data_buffer, buffer);
			// citire primul nr
			if (header->type == '1')
			{
				int8_t nr1;
				int8_t nr2;
				fscanf(stdin, "%"SCNd8 " " "%"SCNd8, &nr1, &nr2);
				// realocare void* data
				data_buffer = realloc(data_buffer, data_len + 1);
				memcpy(data_buffer + data_len, &nr1, 1);
				fscanf(stdin, " ");
				data_len = data_len + 1;
				// realocare void* data
				data_buffer = realloc(data_buffer, data_len + 1);
				memcpy(data_buffer + data_len, &nr2, 1);
				data_len = data_len + 1;
			}
			if (header->type == '2')
			{
				int16_t nr1;
				fscanf(stdin, "%"SCNd16, &nr1);
				// realocare void* data
				data_buffer = realloc(data_buffer, data_len + 2);
				memcpy(data_buffer + data_len, &nr1, 2);
				data_len = data_len + 2;
				int32_t nr2;
				fscanf(stdin, "%"SCNd32, &nr2);
				// realocare void* data
				data_buffer = realloc(data_buffer, data_len + 4);
				memcpy(data_buffer + data_len, &nr2, 4);
				data_len = data_len + 4;
			}
			if (header->type == '3')
			{
				int32_t nr1;
				fscanf(stdin, "%"SCNd32, &nr1);
				// realocare void* data
				data_buffer = realloc(data_buffer, data_len + 4);
				memcpy(data_buffer + data_len, &nr1, 4);
				data_len = data_len + 4;
				int32_t nr2;
				fscanf(stdin, "%"SCNd32, &nr2);
				// realocare void* data
				data_buffer = realloc(data_buffer, data_len + 4);
				memcpy(data_buffer + data_len, &nr2, 4);
				data_len = data_len + 4;
			}
			// citire al doilea nume
			fscanf(stdin, "%s", &buffer);
			data_buffer = realloc(data_buffer, strlen(buffer) + data_len + 1);
			memcpy(data_buffer + data_len, buffer, strlen(buffer) + 1);
			data_len = data_len + strlen(buffer) + 1;
			// alocare data_structure
			data_structure* data_strct = (data_structure*)malloc(sizeof(data_structure));
			data_strct->header = (head*)malloc(sizeof(head));
			data_strct->header->type = header->type;
			data_strct->header->len = data_len;
			;				data_strct->data = (char*)malloc(data_len);
			memcpy(data_strct->data, data_buffer, data_len);
			add_last((void**)&arr, &len, data_strct);

		}
		if ((strcmp("insert_at", command)) == 0)
		{
			int index;
			fscanf(stdin, "%d", &index);
			// citire tip
			fscanf(stdin, "%s", &buffer);
			// alocare header
			head* header = (head*)malloc(sizeof(head));
			//strncpy(header->type, buffer, 1);
			header->type = buffer[0];
			// citire primul nume
			fscanf(stdin, "%s", &buffer);
			// alocare data_buffer
			char* data_buffer = (char*)malloc(strlen(buffer) + 1);
			int data_len = strlen(buffer) + 1;
			strcpy(data_buffer, buffer);
			// citire primul nr
			if (header->type == '1')
			{
				int8_t nr1;
				int8_t nr2;
				fscanf(stdin, "%"SCNd8 " " "%"SCNd8, &nr1, &nr2);
				// realocare void* data
				data_buffer = realloc(data_buffer, data_len + 1);
				memcpy(data_buffer + data_len, &nr1, 1);
				fscanf(stdin, " ");
				data_len = data_len + 1;
				// realocare void* data
				data_buffer = realloc(data_buffer, data_len + 1);
				memcpy(data_buffer + data_len, &nr2, 1);
				data_len = data_len + 1;
			}
			if (header->type == '2')
			{
				int16_t nr1;
				fscanf(stdin, "%"SCNd16, &nr1);
				// realocare void* data
				data_buffer = realloc(data_buffer, data_len + 2);
				memcpy(data_buffer + data_len, &nr1, 2);
				data_len = data_len + 2;
				int32_t nr2;
				fscanf(stdin, "%"SCNd32, &nr2);
				// realocare void* data
				data_buffer = realloc(data_buffer, data_len + 4);
				memcpy(data_buffer + data_len, &nr2, 4);
				data_len = data_len + 4;
			}
			if (header->type == '3')
			{
				int32_t nr1;
				fscanf(stdin, "%"SCNd32, &nr1);
				// realocare void* data
				data_buffer = realloc(data_buffer, data_len + 4);
				memcpy(data_buffer + data_len, &nr1, 4);
				data_len = data_len + 4;
				int32_t nr2;
				fscanf(stdin, "%"SCNd32, &nr2);
				// realocare void* data
				data_buffer = realloc(data_buffer, data_len + 4);
				memcpy(data_buffer + data_len, &nr2, 4);
				data_len = data_len + 4;
			}
			// citire al doilea nume
			fscanf(stdin, "%s", &buffer);
			data_buffer = realloc(data_buffer, strlen(buffer) + data_len + 1);
			memcpy(data_buffer + data_len, buffer, strlen(buffer) + 1);
			data_len = data_len + strlen(buffer) + 1;
			// alocare data_structure
			data_structure* data_strct = (data_structure*)malloc(sizeof(data_structure));
			data_strct->header = (head*)malloc(sizeof(head));
			data_strct->header->type = header->type;
			data_strct->header->len = data_len;
			;				data_strct->data = (char*)malloc(data_len);
			memcpy(data_strct->data, data_buffer, data_len);
			add_at((void**)&arr, &len, data_strct, index);

		}
		if ((strcmp("print", command)) == 0)
		{
			print(arr, len);
		}
		if ((strcmp("find", command)) == 0)
		{
			int index;
			fscanf(stdin, "%d", &index);
			find(arr, len, index);
		}
		if ((strcmp("delete_at", command)) == 0)
		{
			int index;
			fscanf(stdin, "%d", &index);
			delete_at(&arr, &len, index);
		}
		if ((strcmp("exit", command)) == 0)
		{
			return 0;
		}
	}
	return 0;
}
