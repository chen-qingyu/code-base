#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    printf("Content-Type: text/html\n\n");
    printf("<html>");
    printf("<head>");
    printf("<meta charset=\"utf-8\">");
    printf("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    printf("<title>CGI Demo</title>");
    printf("</head>");
    printf("<body>");
    printf("<h1>");
    char* qs = getenv("QUERY_STRING");
    if (qs == NULL || *qs == '\0')
    {
        printf("Hello CGI!");
    }
    else
    {
        printf("Hello %s", qs + strlen("name="));
    }
    printf("</h1></body></html>");

    return 0;
}
