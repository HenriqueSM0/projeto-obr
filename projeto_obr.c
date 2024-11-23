// OBR - ARENA
 
# include <stdio.h>
# include <time.h>
# include <string.h>
# define N 10000
 
char equipes_nomes[N], entry[N];
int equipes_horarios[N];
int i = 0, tmp_j;
 
void hora_atual() {
    time_t current_time;
    time(&current_time);
    struct tm *local_time = localtime(&current_time);
    printf("Hora atual : %02d:%02d:%02d\n",
    local_time->tm_hour,
    local_time->tm_min,
    local_time->tm_sec);
}
 
int marcar_horario() {
    time_t current_time;
    time(&current_time);
    struct tm *local_time = localtime(&current_time);
    int hour, min, j; 
    printf("escreva o horario de inicio na forma -> \033[0;32mhora:min\033[0m :\n");
    scanf("%s%*c", entry);
    if (((entry[0] > 47) && (entry[0] < 58)) && ((entry[1] > 47) && (entry[1] < 58)) && (entry[2] == ':') && 
    ((entry[3] > 47) && (entry[3] < 58)) && ((entry[4] > 47) && (entry[4] < 58)) && (strlen(entry) == 5)) {
        entry[0] = entry[0] - 48;
        entry[1] = entry[1] - 48;
        entry[3] = entry[3] - 48;
        entry[4] = entry[4] - 48;
        hour = entry[0] * 10 + entry[1];
        min = entry[3] * 10 + entry[4];
    }
    if ((min % 10 != 0) || ((min < 0) || (min > 59)) || ((hour < 8) || (hour > 20)))  {
        printf("\033[0;31mNao e possivel marcar nesse horario.\033[0m\n");
        return 0;
    }
    if (hour < local_time->tm_hour) {
        printf("\033[0;31mNao e possivel marcar nesse horario.\033[0m\n");
        return 0;
    } else if ((hour == local_time->tm_hour) && (min < local_time->tm_min)) {
        printf("\033[0;31mNao e possivel marcar nesse horario.\033[0m\n");
        return 0;
    }
    if (i == 0) {
        equipes_horarios[i] = hour * 60 + min;
        printf("Escreva o nome da equipe : \n");
        scanf("%[^\n]%*c", equipes_nomes);
        for (j = 0; equipes_nomes[j] != '\0'; j++) {
            if (equipes_nomes[j + 1] == '\0') {
                equipes_nomes[j + 1] = ';';
                equipes_nomes[j + 2] = '\0';
                break;
            }
        }
        printf("Marcado com sucesso!\n");
        tmp_j = j + 2;
        i++;
    } else {
        if ((hour * 60 + min - equipes_horarios[i - 1]) == 0) {
            printf("\033[0;31mNao e possivel marcar nesse horario. Ele ja foi ocupado.\033[0m\n");
            return 0;
        } else if ((hour * 60 + min - equipes_horarios[i - 1]) > 10) {
            if (hour * 60 + min - local_time->tm_hour * 60 - local_time->tm_min > 10) {
                printf("\033[0;31mNao e possivel marcar nesse horario. Ha um horario disponivel antes.\033[0m\n");
                return 0;
            } 
        } else {
            equipes_horarios[i] = hour * 60 + min;
            printf("Escreva o nome da equipe : \n");
            for (j = tmp_j; equipes_nomes[j - 1] != '\n'; j++) {
                scanf("%c", &equipes_nomes[j]);
            }   
            equipes_nomes[j - 1] = ';';
            printf("Marcado com sucesso!\n");
            tmp_j = j;
            i++;
        }
    }
}

void ver_horarios() {
    time_t current_time;
    time(&current_time);
    struct tm *local_time = localtime(&current_time);
    int k, position = -1;
    for (k = 0; equipes_nomes[k] != '\0'; k++) {
        if (equipes_nomes[k] == ';') {
            position++;
            if (equipes_horarios[position] % 60 == 0) {
                printf("   -------   %d:%d0 ", equipes_horarios[position] / 60, equipes_horarios[position] % 60);
            } else {
                printf("   -------   %d:%d ", equipes_horarios[position] / 60, equipes_horarios[position] % 60);
            }
            if (equipes_horarios[position] > local_time->tm_hour * 60 + local_time->tm_min + 10) {
                printf("(Ensaia daqui a \033[0;32m%02d:%02d\033[0m)\n", (equipes_horarios[position] - (local_time->tm_hour * 60 + local_time->tm_min)) / 60, (equipes_horarios[position] - (local_time->tm_hour * 60 + local_time->tm_min)) % 60);
            } else if (equipes_horarios[position] > local_time->tm_hour * 60 + local_time->tm_min) {
                printf("(Ensaia daqui a \033[0;32m%02d:%02d\033[0m)\n", (equipes_horarios[position] - (local_time->tm_hour * 60 + local_time->tm_min)) / 60, (equipes_horarios[position] - (local_time->tm_hour * 60 + local_time->tm_min)) % 60);
            } else if (equipes_horarios[position] + 10 < local_time->tm_hour * 60 + local_time->tm_min) {
                printf("(Ensaiou a \033[0;31m%02d:%02d\033[0m)\n", (equipes_horarios[position] - (local_time->tm_hour * 60 + local_time->tm_min) - 10) / 60, (equipes_horarios[position] - (local_time->tm_hour * 60 + local_time->tm_min) - 10) % 60);
            } else {
                printf("(Ensaia mais \033[0;33m%02d:%02d\033[0m)\n", (equipes_horarios[position] - (local_time->tm_hour * 60 + local_time->tm_min) + 10) / 60, (equipes_horarios[position] - (local_time->tm_hour * 60 + local_time->tm_min) + 10) % 60);
            }
        } else {
            printf("%c", equipes_nomes[k]);
        }
    }
}
    
void main() {
    char key;
    while(1) {        
        // Features
        printf("Pressione \033[1;34mM\033[0m para marcar um horario :\n");
        printf("Pressione \033[1;34mV\033[0m para ver os horarios marcados :\n");
 
        scanf("%s%*c", entry);
        key = entry[0];
        if ((key == 'm') || (key == 'M')) {
            marcar_horario();
        } else if ((key == 'v') || (key == 'V')) {
            ver_horarios();
        }
    }
}