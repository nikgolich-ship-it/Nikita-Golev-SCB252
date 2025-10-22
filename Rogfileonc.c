#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPENSE 1000

struct Expense
{
    char date[11];
    char category[30];
    float amount;
};

struct Expense expenses[MAX_EXPENSE];
int expcount =0;
void loadExpense(const char *filename)
{
    FILE *file = fopen(filename,"r");
    if (file == NULL)
    {
        return;
    }
    while (expcount < MAX_EXPENSE &&
       fscanf(file, "%10s,%29s,%f",
              expenses[expcount].date,
              expenses[expcount].category,
              &expenses[expcount].amount) == 3)
{
    expcount++;
}

        {
            expcount++;
        }
    fclose(file);
}

void saveChangesToFile(const char *filename, struct Expense random)
{
    FILE *file = fopen(filename,"a");
    if (file == NULL)
    {
        printf("Ошибка при сохранении файла!\n");
        return;
    }
    fprintf(file,"%s,%s,%2.f", random.date,random.category,random.amount);

    fclose(file);
}

void addChange()

{
    if (expcount>=MAX_EXPENSE)
    {
        printf("Превышен лимит расходов!\n");
        return;
    }
    struct Expense random;
     printf("Введите дату (дд.мм.гггг): ");
    scanf("%10s", random.date);
    
    printf("Введите категорию: ");
    scanf("%29s", random.category);
    
    printf("Введите сумму: ");
    scanf("%f", &random.amount);

    expenses[expcount] = random;
    expcount++;
    saveChangesToFile("expense.txt",random);
    printf("Расход добавлен!\n");
}
void showall()
{
    if (expcount==0 )
    {
        printf("Нет данных о расходах.\n");
        return;
    }
    printf("\n--- Все расходы ---\n");
    printf("%-12s%-15s%s\n", "Дата", "Категория", "Сумма");
    printf("------------------------------\n");
    for (int i = 0; expcount>i;i++)

    {
        printf("%-12s%-15s%.2f руб.\n",
            expenses[i].date,
            expenses[i].category,
            expenses[i].amount);
    }
}
void statka()
{
    if (expcount == 0)
    {
        printf("Нет данных для анализа.\n");
        return;
    }
    float total =0;
    float maxexp = -45;
    float sr;
    for (int i =0; i<expcount;i++)
    {
        total+=expenses[i].amount;
        if (expenses[i].amount>maxexp)
        {
            maxexp = expenses[i].amount;
        }
    }
    sr = total/expcount;
    printf("\n--- Статистика ---\n");
    printf("Всего потрачено: %.2f руб.\n", total);
    printf("Средняя трата: %.2f руб.\n", sr);
    printf("Максимальная трата: %.2f руб.\n", maxexp);
}
void menushka()
{
    printf("\n=== Трекер расходов ===\n");
    printf("1. Добавить расход\n");
    printf("2. Показать все расходы\n");
    printf("3. Показать статистику\n");
    printf("4. Выход\n");
    printf("Выберите пункт: ");
}
int main()
{
    loadExpense("expense.txt");
    int choice;
    do 
    {
        menushka();
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            addChange();
            break;
        case 2:
            showall();
            break;
        case 3:
            statka();
            break;
        case 4:
            printf("Выход из программы.\n");
            break;
        default:
            printf("Неверный выбор\n");
            break;
        }
    } while (choice!=4);
    return 0;
}
