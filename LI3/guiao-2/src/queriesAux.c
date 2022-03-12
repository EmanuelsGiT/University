#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../libs/queriesAux.h"

struct countId
{
    int count;
    int id;
};

int cmpCommits(const void* first, const void* second)
{
    int a = GPOINTER_TO_INT((*(COUNTID*)first)->count);
    int b = GPOINTER_TO_INT((*(COUNTID*)second)->count);

    if(a<b) return 1;
    if(a>b) return -1;
    return 0;
}

void insereInArray(gpointer user_id, gpointer count, void *array)
{
    COUNTID cid = malloc(sizeof (struct countId));
    cid->count=GPOINTER_TO_INT(count);
    cid->id=GPOINTER_TO_INT(user_id);
    g_array_append_val(array,cid);
}

void repoWithoutCommit(gpointer repos, gpointer count, void *output)
{
    // Repo1;Descricao1
    if(GPOINTER_TO_INT(count)==0)
        fprintf((FILE*)output, "%d;%s\n", getReposId((REPOS)repos),getReposDescription((REPOS)repos));
}

int insideList(USER user, char* ownerId)
{
    char* folList = getUserFollowersList(user);
    char* folingList = getUserFollowingList(user);

    if (strstr(folList,ownerId)!=NULL && strstr(folingList,ownerId)!=NULL) return 1;

    return 0;
}

int countIdCount(COUNTID c){return c->count;}
int countIdId(COUNTID c){return c->id;}


///////////////////////////////////////////////////////////////////////////////////////////


struct countLang
{
  char lang[21];
  int count;
};

void insereInArrayLang(GArray *array, char *language)
{
  COUNTLANG cid = malloc(sizeof (struct countLang));
  cid->count=1;
  strcpy(cid->lang,language);
  g_array_append_val(array,cid);
}

int searchLang(GArray *array, char *language)
{
  int i, r=-1, len=array->len;
  COUNTLANG c;
  for(i=0; r==-1 && i<len; i++)
  {
    c = g_array_index(array, COUNTLANG, i);
    if(strcmp(language,c->lang)==0) r=i;
  }
  return r;
}

void addCount(GArray *array, int j)
{
  COUNTLANG c = g_array_index(array, COUNTLANG, j);
  c->count=c->count+1;
  g_array_index(array, COUNTLANG, j) = c;
}

int cmpCommitsLang(const void* first, const void* second)
{
    int a = GPOINTER_TO_INT((*(COUNTLANG*)first)->count);
    int b = GPOINTER_TO_INT((*(COUNTLANG*)second)->count);

    if(a<b) return 1;
    if(a>b) return -1;
    return 0;
}

int countLangCount(COUNTLANG c){return c->count;}
char* countLangLang(COUNTLANG c){return c->lang;}


/////////////////////////////////////////////////////////////////////////////////////


struct countIdLog
{
    int count;
    int id;
    char* login;
};


void sortArray(gpointer id, gpointer arrayx, gpointer n_users)
{
  GArray *array = arrayx;
  g_array_sort(array,cmpCommits);
  int i, len = array->len, n_user = GPOINTER_TO_INT(n_users);
  for(i=len-1; i>n_user;i--)
  {
    g_array_remove_index(array,i);
  }
}

void printArray(gpointer id, gpointer arrayx, void *output)
{
  GArray *array = arrayx;
  int i, len = array->len;
  COUNTIDLOG cid;

  for (i=0;i<len;i++)
  {
    cid = g_array_index(array, COUNTIDLOG, i);
    fprintf(output,"%d;%s;%d;%d\n", cid->id, cid->login, cid->count, GPOINTER_TO_INT(id));
  }
}

void insert(int id, int count, char* login, GArray *array)
{
    COUNTIDLOG cid = malloc(sizeof (struct countIdLog));
    cid->id = GPOINTER_TO_INT(id);
    cid->count = GPOINTER_TO_INT(count);
    cid->login = login;
    g_array_append_val(array,cid);
}


////////////////////////////////////////////////////////////////////////////////


int cmpCommits2(const void* first, const void* second)
{
    int a = GPOINTER_TO_INT(first);
    int b = GPOINTER_TO_INT(second);

    if(a<b) return 1;
    if(a>b) return -1;
    return 0;
}

void sortArrayQ(gpointer id, gpointer arrayx, gpointer sum)
{
  GArray *array = arrayx;
  GArray *summ = sum;
  int i, j, len = array->len;
 
  g_array_sort(array,cmpCommits2);
  GArray *array2 = g_array_new( FALSE, TRUE, sizeof(int));
 
  g_array_append_val(array2, g_array_index(array, int, 0));

  for (i = 1, j = 0; i < len; i++)
  {
    if(g_array_index(array, int, i) != g_array_index(array2, int, j))
    {
      g_array_append_val(array2, g_array_index(array, int, i));
      j++;
    }
  }
  g_array_append_val(summ, array2->len);
}