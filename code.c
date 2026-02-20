#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void){
    char *data;
    int n = 0, i, j;

    printf("Content-type: text/html\n\n");
    printf("<html><head>");
    printf("<link rel=\"stylesheet\" href=\"/fint11.css\">");
    printf("<title>Adjacency Matrix</title></head><body>\n");

    printf(" <div class=\"all3\">");
    data = getenv("QUERY_STRING");

    if(data != NULL){
        sscanf(data,"cnt=%d",&n);
        printf("<div>");
        printf("<h3> vertex start at 0 position.... </h3>");
        printf("</div>");
        printf("<div>");
        printf("<form action=\"/cgi-bin/code.exe\" method=\"get\">");
        printf("<input type=\"hidden\" name=\"cnt\" value=\"%d\">", n);
        int k = 1;
        for(i = 0; i < (n*(n-1)/2)+n; i++){
            printf("<input type=\"text\" placeholder=\"TO\" name=\"num%d\"> ", k++);
            printf("<input type=\"text\" placeholder=\"FROM\" name=\"num%d\"> ", k++);
            printf("<br>");
        }
        printf("<input type=\"submit\" value=\"submit\">");
        printf("</form></div>");
    }

    printf("<div class=\"codi\">");
    int f=0;
    if(data != NULL){
        sscanf(data, "cnt=%d", &f);
    }

    int values[20], cntn = 0;
    char qs[500];
    strcpy(qs, data ? data : "");

    char *token = strtok(qs, "&");
    while(token != NULL){
        if(strncmp(token, "num", 3) == 0){
            int temp;
            if(sscanf(token, "num%*d=%d", &temp) == 1){
                values[cntn++] = temp;
            }
        }
        token = strtok(NULL, "&");
    }

    int arr[10][10]={0};
    for(i = 0; i < cntn; i += 2){
        if(i+1 < cntn){
            arr[ values[i] ][ values[i+1] ] = 1;
            arr[ values[i+1] ][ values[i] ] = 1;
        }
    }

    printf("<pre>");
    printf("    ");
    for(i=0;i<f;i++){
        printf("  v%d",i);
    }
    printf("<br>");
    for(i=0;i<f;i++){
        printf("v%d  ",i);
        for(j=0;j<f;j++){
            printf("  %d ",arr[i][j]);
        }
        printf("\n");
    }
    printf("</pre>");
    printf("</div>");
    printf("<div>");
    printf("<h3> edges degree </h3>");

    for(i=0;i<f;i++){
        int deg=0;
        for(j=0;j<f;j++){
            if(i==j && arr[i][j]==1){
                deg+=arr[i][j]+1;
            }else{
                deg+=arr[i][j];
            }
        }
        printf("<h4> v%d = %d DEGREE</h4> ",i,deg);
    }
    printf("</div>");

    printf(" <div class=\"credit\">  Website created by Yashraj</div>");
    printf("</body></html>\n");
    return 0;
}
