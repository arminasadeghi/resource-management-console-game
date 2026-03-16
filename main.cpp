#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int i=1,mardom=50,darbar=50,khazane=50;
struct moshkel{
char soorat[200],tasmim_1[200],tasmim_2[200];
int mardom_1,darbar_1,khazane_1,mardom_2,darbar_2,khazane_2,emkan,node_number,number_f;
struct moshkel *next;
};

struct moshkel * start=NULL;

struct game{
char namee[50];
int state,problem[7],mardom_f,darbar_f,khazane_f;

};
struct game * player;

void add_node(char file_name[]){
    FILE *fp;
    fp=fopen(file_name, "r");
    struct moshkel * current;
    struct moshkel * new_node;
    new_node=(struct moshkel *)malloc(sizeof(struct moshkel));
    current=start;
    char s[5];
    if(start==NULL)
    {
        start=new_node;
        new_node->next=NULL;
        fgets(new_node->soorat,200,fp);
        fgets(new_node->tasmim_1,200,fp);
        fscanf(fp,"%d",&new_node->mardom_1);
        fscanf(fp,"%d",&new_node->darbar_1);
        fscanf(fp,"%d",&new_node->khazane_1);
        fgets(s,5,fp);
        fgets(new_node->tasmim_2,200,fp);
        fscanf(fp,"%d",&new_node->mardom_2);
        fscanf(fp,"%d",&new_node->darbar_2);
        fscanf(fp,"%d",&new_node->khazane_2);
        new_node->emkan=3;
        new_node->node_number=1;
        new_node->number_f=1;
    }
    else
    {
        while(current->next!=NULL)
        {
            current=current->next;
        }
        current->next=new_node;
        new_node->next=NULL;
        fgets(new_node->soorat,200,fp);
        fgets(new_node->tasmim_1,200,fp);
        fscanf(fp,"%d",&new_node->mardom_1);
        fscanf(fp,"%d",&new_node->darbar_1);
        fscanf(fp,"%d",&new_node->khazane_1);
        fgets(s,5,fp);
        fgets(new_node->tasmim_2,200,fp);
        fscanf(fp,"%d",&new_node->mardom_2);
        fscanf(fp,"%d",&new_node->darbar_2);
        fscanf(fp,"%d",&new_node->khazane_2);
        new_node->emkan=3;
        i++;
        new_node->node_number=i;
        new_node->number_f=i;

    }
    fclose(fp);
}

void pp(struct moshkel *ppp){
        printf("%s\n", ppp->soorat);
        printf("1-%s\n", ppp->tasmim_1);
        //printf("%d\n", ppp->mardom_1);
        //printf("%d\n", ppp->darbar_1);
        //printf("%d\n", ppp->khazane_1);
        printf("2-%s\n", ppp->tasmim_2);
        //printf("%d\n", ppp->mardom_2);
        //printf("%d\n", ppp->darbar_2);
        //printf("%d\n", ppp->khazane_2);
}

int randd(){
    time_t t = time(NULL);
    srand(t);
    int ir = rand();
    ir=(ir%i)+1;
    return ir;
}

struct moshkel * choose_node(int ir){
    struct moshkel * current;
    current=start;
    while(current->node_number!=ir)
    {
        current=current->next;
    }
    return current;
}

int delete_node(struct moshkel * current){
    struct moshkel * previous_current;
    int k,t;
    k=current->node_number;
    t=(current->number_f)-1;
    player->problem[t]=0;
    previous_current=start;
    if(current==start)
    {
        start=start->next;
        free(current);
        current=start;
        while(current->next!=NULL)
        {
            current->node_number-=1;
            current=current->next;
        }
        current->node_number-=1;
    }
    else
        {
            while(previous_current->next!=current)
            {
                previous_current=previous_current->next;

            }
            previous_current->next=current->next;
            free(current);
            current=previous_current->next;
            if(current!=NULL)
            {
                while(current->next!=NULL)
                {
                    current->node_number-=1;
                    current=current->next;
                }
                current->node_number-=1;
            }
        }
    i--;
    return(k);
}

void save(struct game *player){
    FILE *fp;
    int j;
    fp=fopen(player->namee, "wb");
    fwrite(&player->state,sizeof(int),1,fp);
    for(j=0;j<7;j++)
    {
        fwrite(&player->problem[j],sizeof(int),1,fp);
    }
    fwrite(&player->mardom_f,sizeof(int),1,fp);
    fwrite(&player->darbar_f,sizeof(int),1,fp);
    fwrite(&player->khazane_f,sizeof(int),1,fp);
    fclose(fp);
}
void recovery(){
    FILE *choicep;
    FILE *node;
    choicep=fopen("CHOICES.txt", "r");
    char file_name[10];
    while(!feof(choicep))
    {
        fscanf(choicep,"%s", file_name);
        add_node(file_name);
    }
    int k;
    for(k=0;k<7;k++)
    {
        player->problem[k]=3;
    }

}
int check()
{
    if((mardom+darbar+khazane)/3<10)
        return 0;
    else if(mardom<=0 || darbar<=0 || khazane<=0)
        return 0;
    else
        return 1;
}

int play(){
    int tasmim,number;
    struct moshkel *current;
    number=randd();
    current=choose_node(number);
    pp(current);
    scanf("%d", &tasmim);
    if(tasmim==3)
    {
        printf("do you want to save the game?\n1)yes\n2)no\n");
        int r;
        scanf("%d", &r);
        if(r==1)
        {
        player->state=check();
        player->mardom_f=mardom;
        player->darbar_f=darbar;
        player->khazane_f=khazane;
            save(player);
        }
            return -1;
    }
    else if(tasmim==1)
    {
        darbar+=current->darbar_1;
        mardom+=current->mardom_1;
        khazane+=current->khazane_1;
    }
    else
    {
        darbar+=current->darbar_2;
        mardom+=current->mardom_2;
        khazane+=current->khazane_2;
    }
    current->emkan--;
    int t;
    t=(current->number_f)-1;
    player->problem[t]--;
    int test;
    if(start->next==NULL && start->emkan==0)
    {
        free(current);
        start=NULL;
        recovery();
    }
    else if(current->emkan==0)
    {
        test=delete_node(current);
    }
    return 0;

}
void old_game(){
    FILE *fp;
    fp=fopen(player->namee, "rb");
    if(fp==NULL)
    {
        printf("Cannot read the file\n");
    }
    fread(&player->state,sizeof(int),1,fp);
    recovery();
    struct moshkel *current;
    int j;
    if(player->state==1)
    {
        current=start;
        for(j=0;j<7;j++)
        {
            fread(&current->emkan,sizeof(int),1,fp);
            current=current->next;
        }
        fread(&mardom,sizeof(int),1,fp);
        fread(&darbar,sizeof(int),1,fp);
        fread(&khazane,sizeof(int),1,fp);
    }
    current=start;
    while(current!=NULL)
    {
        if(current->emkan==0)
        {
            delete_node(current);
            current=start;
        }
        else
            current=current->next;
    }
    fclose(fp);
}

int main(){
    printf("please enter your name\n");
    char name[50];
    gets(name);
    int res;
    player=(struct game *)malloc(sizeof(struct game));
    strcpy(player->namee,name);
    player->state=1;
    printf("\ndo you want to play a new game?\n1.yes\n2.no\n");
    int desicion_number;
    scanf("%d", &desicion_number);
    if(desicion_number==2)
    {
            printf("for quiting please enter 3\n");
            old_game();
            while(check()!=0)
            {
                res=play();
                if(res==-1)
                    break;
                //printf("%d\n%d\n%d\n",mardom,darbar,khazane);
            }
    }
    else
    {
    printf("for quiting please enter 3\n");
    recovery();
    while(check()!=0)
    {
        res=play();
        if(res==-1)
            break;
        printf("%d\n%d\n%d\n",mardom,darbar,khazane);
    }
    int tasmim;
    if(check()==0)
    {
    printf("you lose\n");
    printf("do you want to save the game?\n1)yes\n2)no");
    scanf("%d", &tasmim);
    if(tasmim==1)
    {
        player->state=check();
        player->mardom_f=mardom;
        player->darbar_f=darbar;
        player->khazane_f=khazane;
        save(player);
    }
    }
    }
    printf("game finished");
    free(player);
    return 0;
}
