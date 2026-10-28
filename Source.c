#include <stdio.h>
#include <locale.h>
#include <math.h>

#define COMPONENT_COUNT 3
#define SAMPLE_COUNT 5

int main(void)
{
    const int k = 2;
    const float limit = 0.8f;
    const int required_problem_count = 1;
    const char *component_names[COMPONENT_COUNT] = { "QUE", "TLS", "DNS" };
    const float measurements[COMPONENT_COUNT][SAMPLE_COUNT] = {
        { 43.7f, 44.2f, 44.7f, 50.6f, 51.1f },
        { 53.8f, 57.2f, 55.2f, 53.2f, 51.2f },
        { 32.0f, 31.3f, 30.6f, 35.2f, 34.5f }
    };
    int sample;
    int component;
    int problem_count;
    int incident_count = 0;
    int is_problem;
    int is_incident;
    float indicator;

    setlocale(LC_CTYPE, "RUS");

    printf("Здравствуйте! Программа проверяет состояние компонентов QUE, TLS и DNS.\n");
    printf("Вариант 8. Пять отсчётов, k = %d, L = %.1f.\n", k, limit);
    printf("\nИсходные данные:\n");
    printf("Отсчёт  QUE   TLS   DNS\n");

    for (sample = 0; sample < SAMPLE_COUNT; sample++) {
        printf("%d", sample + 1);
        for (component = 0; component < COMPONENT_COUNT; component++) {
            printf("  %.1f", measurements[component][sample]);
        }
        printf("\n");
    }

    printf("\nДля отсчётов 1 и 2 недостаточно предыдущих данных.\n");

    for (sample = k; sample < SAMPLE_COUNT; sample++) {
        problem_count = 0;
        printf("\nОтсчёт %d:\n", sample + 1);

        for (component = 0; component < COMPONENT_COUNT; component++) {
            indicator = measurements[component][sample] / measurements[component][sample - k];
            is_problem = fabsf(indicator) > limit;
            problem_count += is_problem;
            printf("%s: Q = %.4f, ", component_names[component], indicator);

            if (is_problem) {
                printf("ТРЕВОГА\n");
            }
            else {
                printf("НОРМА\n");
            }
        }

        is_incident = problem_count == required_problem_count;
        incident_count += is_incident;
        printf("Проблемных компонентов: %d. ", problem_count);

        if (is_incident) {
            printf("Инцидент есть.\n");
        }
        else {
            printf("Инцидента нет.\n");
        }
    }

    printf("\nВсего инцидентов: %d.\n", incident_count);

    return 0;
}
