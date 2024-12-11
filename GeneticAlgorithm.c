#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUM_CITIES 8
#define POP_SIZE 8
#define MAX_GEN 1000
#define CROSSOVER_RATIO 1.0
#define MUTATION_RATIO 0.01

typedef struct {
    int path[NUM_CITIES];
    double fitness;
} Individual;

double coordinates[NUM_CITIES][2] = {
    {0, 3}, {7, 5}, {6, 0}, {4, 3}, {1, 0}, {5, 3}, {4, 1}, {2, 2}
};

// Function to calculate distance between two cities
double distance(int a, int b) {
    double dx = coordinates[a][0] - coordinates[b][0];
    double dy = coordinates[a][1] - coordinates[b][1];
    return sqrt(dx * dx + dy * dy);
}

// Function to calculate total path distance
double calculate_fitness(int path[]) {
    double total_distance = 0;
    for (int i = 0; i < NUM_CITIES - 1; i++) {
        total_distance += distance(path[i], path[i + 1]);
    }
    total_distance += distance(path[NUM_CITIES - 1], path[0]); // Return to start
    return total_distance;
}

// Generate a random individual
void generate_individual(Individual *ind) {
    ind->path[0] = 0; // Starting point fixed at A
    for (int i = 1; i < NUM_CITIES; i++) {
        ind->path[i] = i;
    }
    for (int i = 1; i < NUM_CITIES; i++) { // Shuffle cities except the first
        int j = 1 + rand() % (NUM_CITIES - 1);
        int temp = ind->path[i];
        ind->path[i] = ind->path[j];
        ind->path[j] = temp;
    }
    ind->fitness = calculate_fitness(ind->path);
}

// Perform crossover (Cycle Crossover)
void crossover(int parent1[], int parent2[], int child[]) {
    int visited[NUM_CITIES] = {0};
    int start = 1 + rand() % (NUM_CITIES - 1); // Start at a random position
    int current = start;

    while (!visited[current]) {
        child[current] = parent1[current];
        visited[current] = 1;
        // Find the position of this city in parent2
        for (int i = 1; i < NUM_CITIES; i++) {
            if (parent2[i] == parent1[current]) {
                current = i;
                break;
            }
        }
    }

    // Fill remaining positions with parent2's order
    for (int i = 1; i < NUM_CITIES; i++) {
        if (!visited[i]) {
            child[i] = parent2[i];
        }
    }
    child[0] = 0; // Ensure starting point is A
}

// Perform mutation (swap two random cities)
void mutate(Individual *ind) {
    if ((double)rand() / RAND_MAX < MUTATION_RATIO) {
        int i = 1 + rand() % (NUM_CITIES - 1);
        int j = 1 + rand() % (NUM_CITIES - 1);
        int temp = ind->path[i];
        ind->path[i] = ind->path[j];
        ind->path[j] = temp;
        ind->fitness = calculate_fitness(ind->path);
    }
}

// Perform selection (tournament selection)
int select_parent(Individual population[]) {
    int a = rand() % POP_SIZE;
    int b = rand() % POP_SIZE;
    return (population[a].fitness < population[b].fitness) ? a : b;
}

// Genetic Algorithm implementation
void genetic_algorithm() {
    Individual population[POP_SIZE];
    Individual new_population[POP_SIZE];

    // Initialize population
    for (int i = 0; i < POP_SIZE; i++) {
        generate_individual(&population[i]);
    }

    for (int gen = 0; gen < MAX_GEN; gen++) {
        // Create new population
        for (int i = 0; i < POP_SIZE; i++) {
            int parent1 = select_parent(population);
            int parent2 = select_parent(population);
            if ((double)rand() / RAND_MAX < CROSSOVER_RATIO) {
                crossover(population[parent1].path, population[parent2].path, new_population[i].path);
            } else {
                for (int j = 0; j < NUM_CITIES; j++) {
                    new_population[i].path[j] = population[parent1].path[j];
                }
            }
            new_population[i].fitness = calculate_fitness(new_population[i].path);
            mutate(&new_population[i]);
        }

        // Replace population with new population
        for (int i = 0; i < POP_SIZE; i++) {
            population[i] = new_population[i];
        }
    }

    // Find best solution
    Individual best = population[0];
    for (int i = 1; i < POP_SIZE; i++) {
        if (population[i].fitness < best.fitness) {
            best = population[i];
        }
    }

    // Output best solution
    printf("Best path: ");
    for (int i = 0; i < NUM_CITIES; i++) {
        printf("%c ", 'A' + best.path[i]);
    }
    printf("\nTotal distance: %.2f\n", best.fitness);
}

int main() {
    srand(time(NULL));
    genetic_algorithm();
    return 0;
}
