#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char* JSON_GetItemCaseSensitive(char *s , char* key)
{
    char ans[1024] , h[1024] = {0};
    int cnt = 0 , add = 0 , n = 0;
    bool check = 0;
    for(int i = 0; i < strlen(s); i++){
        if(s[i] == '"') {
            if (cnt % 2)
                cnt++, add = 0;
            else {
                cnt++, add = 1;
                if(strcmp(h , key) == 0) {
                    check = 1;
                }
                memset(h , 0 , sizeof(h));
                n = 0;
            }
            if(!check)
                continue;
        }
        if(check){
            int j = i , c = 0;
            if(s[j - 1] == '[' || s[j - 1] == '{')
                j = i - 1;
            n = 0;
            if(s[j] == '"'){
                while(true){
                    if(s[j] == '"')
                        c++;
                    ans[n++] = s[j++];
                    if(c == 2)
                        break;
                }
            }
            if(s[j] == '[' || s[j] == '{'){
                while(true){
                    ans[n++] = s[j++];
                    if(s[j] == ']' || s[j] == '}') {
                        ans[n++] = s[j];
                        ans[n] = '\0';
                        break;
                    }
                }
            }
            char* t = ans;
            printf("%s\n", ans);
            return t;
        }
        if(add)
            h[n++] = s[i];
    }
    return ans;
}

void addItemtoString(char** s , char* type, char* content)
{
    char t[1024] = {0};
    for(int i = 0; i < strlen(*s) - 1; i++)
        t[i] = (*s)[i];
    if(strlen(*s) != 2)
        strcat(t, ",");
    if(content[0] == '[' || content[0] == '{')
        sprintf(t + strlen(t), "\"%s\":%s}" , type , content);
    else
        sprintf(t + strlen(t), "\"%s\":\"%s\"}" , type , content);
    *s = t;
    return;
}

void addItemtoArray(char** s, char* item)
{
    char t[1024] = {0};
    strncpy(t , *s , strlen(*s) - 1);
    if(strlen(*s) != 2)
        strcat(t , ",");
    sprintf(t + strlen(t) , "\"%s\"]" , item);
    *s = t;
    return;
}

int main()
{
}