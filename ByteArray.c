#include "ByteArray.h"

ByteArray *createByteArray()
{
    ByteArray *array = (ByteArray *)malloc(sizeof(ByteArray));
    if (!array)
    {
        printf("ERROR: Failed to allocate memory for ByteArray\n");
        return NULL;
    }

    array->data = NULL;
    array->size = 0;
    return array;
}

int freeByteArray(ByteArray *a)
{
    if (!a) return -1; // Failure, array was NULL
    if(a->data)
    {
        free(a->data);
        a->data = NULL; // Set data to NULL after freeing
    }
    free(a);
    return 0; // Success
}

int appendToByteArray(ByteArray *array, const void *data, size_t size)
{
    size_t newSize = array->size + size;
    char *newData = realloc(array->data, newSize);
    if (!newData)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }

    memcpy(newData + array->size, data, size);
    array->data = newData;
    array->size = newSize;

    return 0;
}

int removeFromByteArray(ByteArray *array, size_t startPoint, size_t length)
{
    if (startPoint < 0 || length < 0)
    {
        printf("ERROR: invalid range: startPoint=%d, length=%d\n", startPoint, length);
        return -1;
    }
    else if (array == NULL || array->data == NULL)
    {
        printf("ERROR: ByteArray is null\n");
        return -1;
    }
    else if (array->size < (startPoint + length))
    {
        printf("ERROR: range [%d, %d) exceeds buffer size (%zu)\n", startPoint, startPoint + length, array->size);
        return -1;
    }

    else
    {

        if (startPoint == 0)
        {
            array->size -= length;
            char *newData = (char *)malloc(array->size);
            if (newData == NULL)
            {
                printf("ERROR: malloc failed\n");
                return -1;
            }

            memmove(newData, array->data + length, array->size);
            free(array->data);
            array->data = newData;
        }

        else if (startPoint + length == array->size)
        {
            array->size -= length;
        }
        else
        {
            size_t newSize = array->size - length;
            char *BeginData = (char *)malloc(startPoint);
            char *EndData = (char *)malloc(array->size - startPoint - length);

            if (!BeginData || !EndData)
            {
                // Обработка ошибки аллокации
                free(BeginData);
                free(EndData);
                return -1;
            }

            memmove(BeginData, array->data, startPoint);
            memmove(EndData, array->data + startPoint + length, array->size - startPoint - length);

            free(array->data);
            array->data = (char *)malloc(newSize);

            if (!array->data)
            {
                // Если аллокация не удалась — очищаем и возвращаем
                free(BeginData);
                free(EndData);
                array->size = 0;
                return -1;
            }

            memmove(array->data, BeginData, startPoint);
            memmove(array->data + startPoint, EndData, array->size - startPoint - length);

            free(BeginData);
            free(EndData);
            array->size = newSize;
        }
    }
    printf("removeFrome byte array: ");
}

void showMessage(ByteArray *message)
{
    printf("\nshowMessage: ");
    for (int i = 0; i < message->size; i++)
        printf("%X ", message->data[i]);
    printf("\n");
}