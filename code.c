#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Função para calcular o MDC usando o algoritmo de Euclides
int mdc(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Função para verificar se um número é primo
int eh_primo(int num) {
    if (num <= 1) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;
    
    for (int i = 3; i * i <= num; i += 2) {
        if (num % i == 0) return 0;
    }
    return 1;
}

// Função para calcular o inverso modular usando o algoritmo estendido de Euclides
int inverso_modular(int G, int n) {
    int m0 = n, t, q;
    int x0 = 0, x1 = 1;
    
    if (n == 1) return 0;
    
    while (G > 1) {
        q = G / n;
        t = n;
        
        n = G % n;
        G = t;
        
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    
    if (x1 < 0) x1 += m0;
    
    return x1;
}

// Função totiente de Euler
int phi(int n) {
    int resultado = n;
    
    for (int p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            while (n % p == 0)
                n /= p;
            resultado -= resultado / p;
        }
    }
    
    if (n > 1)
        resultado -= resultado / n;
    
    return resultado;
}

// Função para exponenciação modular eficiente
int exp_modular(int base, int expoente, int modulo) {
    int resultado = 1;
    base = base % modulo;
    
    while (expoente > 0) {
        if (expoente % 2 == 1)
            resultado = (resultado * base) % modulo;
        
        expoente = expoente >> 1;
        base = (base * base) % modulo;
    }
    
    return resultado;
}

int main() {
    int H, G, n, x, n1;
    
    printf("Digite os valores de H, G e n: ");
    scanf("%d %d %d", &H, &G, &n);
    
    printf("Digite o expoente x: ");
    scanf("%d", &x);
    
    printf("Digite o módulo n1: ");
    scanf("%d", &n1);
    
    int gcd = mdc(G, n);
    if (gcd != 1) {
        printf("Divisão não é possível pois G e n não são coprimos (MDC(%d, %d) = %d)\n", G, n, gcd);
        return 0;
    }
    
    // Passo 2: Calcular o inverso de G em Zn
    int G_inv = inverso_modular(G, n);
    printf("Inverso de G em Zn: %d\n", G_inv);
    
    // Calcular a base a = (H * G_inv) mod n
    int a = (H % n) * (G_inv % n) % n;
    printf("Base a calculada: %d\n", a);
    
    // Passo 3: Verificar se a e n1 são coprimos
    gcd = mdc(a, n1);
    if (gcd != 1) {
        printf("a e n1 não são coprimos (MDC(%d, %d) = %d)\n", a, n1, gcd);
    } else {
        printf("a e n1 são coprimos\n");
    }
    
    // Passo 4 e 5: Verificar se n1 é primo e aplicar Fermat ou Euler
    int x1;
    if (eh_primo(n1)) {
        printf("n1 é primo - aplicando Pequeno Teorema de Fermat\n");
        x1 = n1 - 1;
    } else {
        printf("n1 não é primo - aplicando Teorema de Euler\n");
        x1 = phi(n1);
    }
    
    // Otimizar o expoente usando x1
    int exp_otimizado = x % x1;
    printf("Expoente otimizado: %d\n", exp_otimizado);
    
    // Calcular a^x mod n1
    int resultado = exp_modular(a, x, n1);
    printf("Resultado final: %d^%d mod %d = %d\n", a, x, n1, resultado);
    
    return 0;
}
