#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    int min = 2000000000, max = 0, n, save;
    scanf ("%d", &n);
    
    while (n--) {
        scanf ("%d", &save);
        if (save < min)
            min = save;
        if (save > max)
            max = save;
        
        printf ("%d\n", min + max);
    }
    
    return 0;
}
