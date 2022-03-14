#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


typedef struct s_list{
    long long num;
    struct s_list *next;
}   t_list;

t_list *lst_new(long long num)
{
    t_list *new;

    if(!(new = malloc(sizeof(t_list))))
        return (NULL);
    new->num = num;
    new->next = NULL;
    return (new);
}

void lstadd_front(t_list *lst, t_list **alst)
{
    lst->next = *alst;
    alst = &lst;
}

long long summ_of(long long n)
{
    long long res;

    res = 0;
    while (n != 0)
    {
        res += (int)n % 10;
        n /= 10;
    }
    return (res);
}

long long meet(t_list **alst_a, t_list **alst_b)
{
    t_list *lst_a;
    t_list *lst_b;

    lst_a = *alst_a;
    lst_b = *alst_b;
    while (lst_a)
    {
        while (lst_b)
        {
            if (lst_b->num == lst_a->num)
                return (lst_a->num);
            lst_b = lst_b->next;
        }
        lst_a = lst_a->next;
    }
    return (-1);
}

void add_next_10(t_list **alst)
{
    int i;

    i = 0;
    while (i < 10)
    {
        lstadd_front(lst_new(((*alst)->num) + summ_of((*alst)->num)), alst);        
        i++;
    }
}

long long supply(t_list **alst_a, t_list **alst_b)
{
    long long res;

    res = -1;
    while (res == -1)
    {
        add_next_10(alst_a);
        add_next_10(alst_b);
        res = meet(alst_a, alst_b);
    }
    return (res);
}

int main()
{
    long long r_1;
    scanf("%lld", &r_1);
    long long r_2;
    scanf("%lld", &r_2);

    t_list **alst_a, **alst_b;
    t_list *lst_a, *lst_b;
    lst_a = lst_new(r_1);
    lst_b = lst_new(r_2);
    alst_a = &lst_a;
    alst_b = &lst_b;
    printf("%lld\n", supply(alst_a, alst_b));

    return 0;
}