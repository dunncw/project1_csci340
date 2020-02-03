#include <stdio.h>
#include <ctype.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>


int check(char string[]){

    int length = strlen(string);
    //int test_i;

    //printf("%d\n", length);

    for(int walk = 0; walk <= length; walk++){
        //test_i = isdigit(string[walk]);
        //printf("walk: %d char: %c test_i: %d\n", walk, string[walk], test_i);
        if(isdigit(string[walk]) == 0 && string[walk] != '\0'){
            
            return 0;
        }
    }
    
    return 1;
}

/*
struct t_node { 
    int pid;
    int ppid;
    struct t_node *right; 
};

struct t_node* newNode(int pid, int ppid) { 
  // Allocate memory for new node  
  struct t_node* node = (struct node*)malloc(sizeof(struct node)); 
  
  // Assign data to this node 
  t_node->pid = pid; 
  t_node->ppid = ppid;

  //pointer back to that parent
  t_node->parent = NULL; 
  return(t_node); 
}*/

struct node* print_process_tree(struct node * rt, int level, struct node* head) {

    printf("in fucntion: head <%p>, &head <%p>\n", head, &head);

    

/*
    while (temp != NULL) {

        printf("pid <%d>, ppid <%d>,vsize <%d>\n",
               temp->pid, temp->ppid, temp->vsize);
/*
        if(temp->ppid == 0){
        rt->pid = temp->pid;
        rt->ppid = temp->ppid;
        rt->vsize = temp->Vsize;
        strcpy(rt->final, temp->final);
        rt->sub_p = NULL;

        printf("(%d) %s, %d kb\n",
               rt->pid, rt->final + 1, rt->vsize);
        }


        temp = temp->sub_p;
    }
*/
    return rt;
}



typedef struct node{
    int pid;
    int ppid;
    char final[100];
    int vsize;

    struct node *sub_p;
} node;


int main(void)
{
    struct dirent *de;  // Pointer for directory entry
  
    // opendir() returns a pointer of DIR type. 
    DIR *dr = opendir("/proc");
  
    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return 0;
    }

    
    struct node *head = NULL;
    struct node *n_prev = NULL;

    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
    // for readdir()
    while ((de = readdir(dr)) != NULL){
        if(check(de->d_name) >= 1){
            char file_n[] = "/proc/";
            strcat(file_n, de->d_name);
            strcat(file_n, "/stat");
        

            FILE *fp; //create a file data type so you can pass somthing to fopen
        


            //info on each file

            int pid; //this files pid
            int ppid;  // this files ppid
            char executable[100];  //this files name of its executable 
            int Vsize; // this files vsize

            
            fp= fopen(file_n, "r");

            
            if(fp == NULL){
            }
            else{
                fscanf(fp, "%d %s %*s %d %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %d", &pid, executable, &ppid, &Vsize);
                fclose(fp); 
            } 
            
/*
            char *p = executable;
            if (executable[0] == '\n') 
                memmove(executable, executable+1, strlen(executable));
            
            p[strlen(p)-1] = '\0';
*/
            //printf("%d %s, %d kb, PPID<%d>\n", pid, executable, Vsize, ppid);
            /*      
            fp= fopen("/proc/1/stat", "r");

            if(fp == NULL){ }
            while (fgets(str_1, 1000, fp) != NULL)
                    printf("%s \n", str_1);
            fclose(fp);  
            */

            char *p = executable;
            p[strlen(p)-1] = '\0';

            //make nodes for trees
            struct node *n_new = malloc(sizeof(struct node));
            
            n_new->pid = pid;
            n_new->ppid = ppid;
            n_new->vsize = Vsize;
            strcpy(n_new->final, executable); 
            n_new->sub_p = NULL;


            //make a simple list firt
            if (head == NULL)
                    head = n_new;
                else
                    n_prev->sub_p = n_new;
                    
             // Save this nodes address
                
             n_prev = n_new;

            
        }
          

    }

/*
    struct node *node = head;

    while (node != NULL) {

        printf("pid <%d>, ppid <%d>,vsize <%d>\n",
               node->pid, node->ppid, node->vsize);

        node = node->sub_p;
    }  
*/


    struct node *rt = NULL;
    
    print_process_tree(rt, 0, head);
    printf("head in main: head <%p>, &head<%p>, head->pid<%d>\n", head, &head, head->pid);
    

    closedir(dr);     
    return 0;
}

