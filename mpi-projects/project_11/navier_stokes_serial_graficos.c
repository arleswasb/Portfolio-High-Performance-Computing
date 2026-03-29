#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NT 6000

// Funções de alocação/liberação (sem alterações)
double** allocate_grid(int nx, int ny) {
    double *data = (double*)malloc(nx * ny * sizeof(double));
    double **array = (double**)malloc(nx * sizeof(double*));
    for (int i = 0; i < nx; i++) {
        array[i] = &(data[i * ny]);
    }
    return array;
}

void free_grid(double** array) {
    free(array[0]);
    free(array);
}

// --- NOVA FUNÇÃO PARA SALVAR A GRADE ---
void save_grid_to_file(const char* filename, double** grid, int nx, int ny) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", filename);
        return;
    }
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            fprintf(fp, "%.6f ", grid[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <TAMANHO_DA_GRADE>\n", argv[0]);
        return 1;
    }
    int NX = atoi(argv[1]);
    int NY = NX;

    double **u = allocate_grid(NX, NY);
    double **v = allocate_grid(NX, NY);
    double **u_new = allocate_grid(NX, NY);
    double **v_new = allocate_grid(NX, NY);
    
    // Inicialização com perturbação
    for (int i = 0; i < NX; i++) {
        for (int j = 0; j < NY; j++) {
            u[i][j] = 1.0; v[i][j] = 0.0;
            double dx = i - NX/2.0, dy = j - NY/2.0;
            double dist = sqrt(dx*dx + dy*dy);
            if (dist < (NX / 25.0)) {
                u[i][j] += 2.0 * exp(-dist*dist/(NX/5.0));
                v[i][j] += 1.5 * exp(-dist*dist/(NX/5.0));
            }
        }
    }
    
    // --- SALVANDO O ESTADO INICIAL (PASSO 0) ---
    printf("Salvando estado inicial (passo 0)...\n");
    save_grid_to_file("u_step_0.txt", u, NX, NY);
    save_grid_to_file("v_step_0.txt", v, NX, NY);

    clock_t start_time = clock();
    
    for (int step = 0; step < NT; step++) {
        // ... (Cálculo principal e condições de contorno - sem alterações) ...
        for (int i = 1; i < NX-1; i++) {
            for (int j = 1; j < NY-1; j++) {
                double d2u_dx2 = (u[i+1][j] - 2.0*u[i][j] + u[i-1][j]);
                double d2u_dy2 = (u[i][j+1] - 2.0*u[i][j] + u[i][j-1]);
                double d2v_dx2 = (v[i+1][j] - 2.0*v[i][j] + v[i-1][j]);
                double d2v_dy2 = (v[i][j+1] - 2.0*v[i][j] + v[i][j-1]);
                u_new[i][j] = u[i][j] + (0.001 * 0.01) * (d2u_dx2 + d2u_dy2);
                v_new[i][j] = v[i][j] + (0.001 * 0.01) * (d2v_dx2 + d2v_dy2);
            }
        }
        for (int i = 0; i < NX; i++) {
            u_new[i][0] = u_new[i][NY-2]; u_new[i][NY-1] = u_new[i][1];
            v_new[i][0] = v_new[i][NY-2]; v_new[i][NY-1] = v_new[i][1];
        }
        for (int j = 0; j < NY; j++) {
            u_new[0][j] = u_new[NX-2][j]; u_new[NX-1][j] = u_new[1][j];
            v_new[0][j] = v_new[NX-2][j]; v_new[NX-1][j] = v_new[1][j];
        }
        
        double **temp_u = u; double **temp_v = v;
        u = u_new; v = v_new;
        u_new = temp_u; v_new = temp_v;

        // --- SALVANDO ESTADOS INTERMEDIÁRIO E FINAL ---
        if (step == 500) {
            printf("Salvando estado intermediário (passo 501)...\n");
            save_grid_to_file("u_step_501.txt", u, NX, NY);
            save_grid_to_file("v_step_501.txt", v, NX, NY);
        }
    }
    
    clock_t end_time = clock();
    
    printf("Salvando estado final (passo %d)...\n", NT);
    save_grid_to_file("u_step_final.txt", u, NX, NY);
    save_grid_to_file("v_step_final.txt", v, NX, NY);
    
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %.6f segundos\n", elapsed_time);
    
    free_grid(u); free_grid(v); free_grid(u_new); free_grid(v_new);
    
    return 0;
}