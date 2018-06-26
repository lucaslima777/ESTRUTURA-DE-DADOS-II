#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

void eixo_x_y(int x, int y);

struct struct_element
{
    int number_id;        
    int value;     
    int value_def; 

    char value_DB[1];   

    struct struct_element *nodo_father;     
    struct struct_element *nodo_left; 
    struct struct_element *nodo_right;  
    int level_nodo;
};

void Tree(){
	eixo_x_y(20,2); printf("(+) \n");
	eixo_x_y(20,3); printf("/ \\");
	eixo_x_y(19,4); printf("/   \\");
	eixo_x_y(17,5); printf("(*)   (5)");
	eixo_x_y(17,6); printf("/ \\");
	eixo_x_y(16,7); printf("/   \\");
	eixo_x_y(15,8); printf("/     \\");
	eixo_x_y(14,9); printf("/       \\");
	eixo_x_y(12,10); printf("(-)       (+)");
	eixo_x_y(12,11); printf("/ \\");
	eixo_x_y(11,12); printf("/   \\");
	eixo_x_y(9,13); printf("(6)   (3)");
	eixo_x_y(22,11); printf("/ \\");
	eixo_x_y(21,12); printf("/   \\");
	eixo_x_y(19,13); printf("(4)   (1)");
}

struct struct_element *nodo_raiz = NULL;
int nstruct_elements = 0;
int ASCII_I = 48; 
int ASCII_II = 57;
int nlevel_nodo = 0;

	struct struct_element *New_NO(char *value_DB, struct struct_element *nodo_pai)
{

    struct struct_element *tree_nodo = malloc(sizeof(struct struct_element));
    if (tree_nodo == NULL)
    {
        printf("insufficient memory");
        return NULL;
    }
    nstruct_elements++;
    tree_nodo->number_id = nstruct_elements;
    tree_nodo->value = 0;
    strcpy(tree_nodo->value_DB, " ");
    tree_nodo->value_DB[0] = value_DB[0];
    tree_nodo->value_def = 0;
    tree_nodo->nodo_left = NULL;
    tree_nodo->nodo_right = NULL;
    tree_nodo->nodo_father = nodo_pai;
    tree_nodo->level_nodo = 0;

    if (nodo_pai == NULL)
    {
        tree_nodo->level_nodo = 1;
    }
    else
    {
        tree_nodo->level_nodo = nodo_pai->level_nodo + 1;
    }
    return tree_nodo;
}

void eixo_x_y(int x, int y)
{
    HANDLE hCon;
    COORD dwPos;

    dwPos.X = x;
    dwPos.Y = y;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon,dwPos);
}

void buffer(struct struct_element *no)
{
    if (no == NULL)
    {
        return;
    }
    if (no->nodo_left != NULL)
    {
        buffer(no->nodo_left);
        no->nodo_left = NULL;
    }
    if (no->nodo_right != NULL)
    {
        buffer(no->nodo_right);
        no->nodo_right = NULL;
    }
    free(no);
}

void New_Tree()
{
    nstruct_elements = 0;
    nodo_raiz = New_NO("+", NULL);
    nodo_raiz->nodo_left = New_NO("*", nodo_raiz);
    nodo_raiz->nodo_right = New_NO("5", nodo_raiz);
    nodo_raiz->nodo_left->nodo_left = New_NO("-", nodo_raiz->nodo_left);
    nodo_raiz->nodo_left->nodo_right = New_NO("+", nodo_raiz->nodo_left);
    nodo_raiz->nodo_left->nodo_left->nodo_left = New_NO("6", nodo_raiz->nodo_left->nodo_left);
    nodo_raiz->nodo_left->nodo_left->nodo_right = New_NO("3", nodo_raiz->nodo_left->nodo_left);
    nodo_raiz->nodo_left->nodo_right->nodo_left = New_NO("4", nodo_raiz->nodo_left->nodo_right);
    nodo_raiz->nodo_left->nodo_right->nodo_right = New_NO("1", nodo_raiz->nodo_left->nodo_right);

}


int calc_nodo(struct struct_element *nodo)
{
	int nivel = 0;
    if (nodo == NULL)
    {
        return 0;
    }

    if (nodo->value_def == 0)
    {
        short n = (short)nodo->value_DB[0];
        if (n >= ASCII_I && n <= ASCII_II)
        {
            nodo->value = (short)nodo->value_DB[0] - ASCII_I;
            nodo->value_def = 1;
        }
        else
        {
        	
            nlevel_nodo++;
            int value_left = calc_nodo(nodo->nodo_left);
            int value_right = calc_nodo(nodo->nodo_right);
            nlevel_nodo--;
            switch (n)
            {
            case 43:
                nodo->value = value_left + value_right;
                nodo->value_def = 1;
                printf("Nodo %d: %d + %d = %d\n", nodo->number_id, value_left, value_right, nodo->value);
                break;
            case 45:
                nodo->value = value_left - value_right;
                nodo->value_def = 1;
                eixo_x_y(0,16);
                printf("Nodo %d: %d - %d = %d\n", nodo->number_id, value_left, value_right, nodo->value);
                break;
            case 42:
                nodo->value = value_left * value_right;
                nodo->value_def = 1;
                eixo_x_y(0,18);
                printf("Nodo %d: %d * %d = %d\n", nodo->number_id, value_left, value_right, nodo->value);
                nivel++;
                break;
            case 47:
                if (value_right != 0)
                {
                    nodo->value = value_left / value_right;
                }
                else
                {
                    nodo->value = 0;
                }
                printf("Nodo %d: %d / %d = %d\n", nodo->number_id, value_left, value_right, nodo->value);
                nodo->value_def = 1;
                break;
            default:
                printf("ERROR[%s]\n", nodo->value_DB[0]);
                break;
            }
        }
    }
    else
    {
        printf("Resultado = %d\n", nodo->value);
    }
    return nodo->value;
}



int main()
{
    Tree();
    New_Tree();
    int Calculo = calc_nodo(nodo_raiz);
    printf("\nTotal: %d\n\n", Calculo);
    buffer(nodo_raiz);
    return Calculo;
}
