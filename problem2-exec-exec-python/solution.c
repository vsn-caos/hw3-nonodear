#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Программе на стандартный поток ввода задается арифметическое выражение
// в синтаксисе языка python3. Необходимо вычислить это выражение и вывести результат.
// Использовать дополнительные процессы запрещено — нужно использовать exec.

int main(void) {
    // TODO: прочитайте выражение из stdin,
    //       затем вызовите execvp/execlp для запуска python3,
    //       который вычислит и выведет результат.
    //       Подсказка: python3 -c "print(<выражение>)"
    char expr[4096];
    
    if (fgets(expr, sizeof(expr), stdin) == NULL) {
        return 0; 
    }
    size_t len = strlen(expr);
    if (len > 0 && expr[len - 1] == '\n') {
        expr[len - 1] = '\0';
    }
    char script[8192];
    
    snprintf(script, sizeof(script), "print(%s)", expr);
    execlp("python3", "python3", "-c", script, NULL);
    perror("execlp");
    return 1;

    

    return 0;
}
