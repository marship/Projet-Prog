#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "lecture_symbole.h"
#include "fonctions_utilitaires.h"
#include "string_table.h"

// Numéro de Section
int noSection;

// Nombre de Symbole
int nbSym;

Elf32_Sym *lire_symbole(char *nom_fichier, Elf32_Ehdr ehdr, Elf32_Shdr *shdr)
{
    FILE *f;

    // Recherche de la section des symboles
    noSection = 0;

    while (shdr[noSection].sh_type != SHT_SYMTAB && noSection < ehdr.e_shnum)
    {
        noSection++;
    }

    if (noSection == ehdr.e_shnum)
    {
        fprintf(stderr, "Erreur: symbol table absente\n");
        exit(EXIT_FAILURE);
    }

    // Calcul du nombre de symboles
    nbSym = shdr[noSection].sh_size / shdr[noSection].sh_entsize;

    // Allocation de la place nécessaire
    Elf32_Sym *sym = malloc(nbSym * sizeof(Elf32_Sym));

    // Ouverture du fichier
    f = fopen(nom_fichier, "rb");

    if (f == NULL)
    {
        fprintf(stderr, "Impossible d'ouvir le fichier : %s\n", nom_fichier);
        exit(EXIT_FAILURE);
    }

    // Deplacement au début des symboles
    if (fseek(f, shdr[noSection].sh_addr + shdr[noSection].sh_offset, SEEK_SET) != 0)
    {
        fprintf(stderr, "Erreur de lecture du fichier %s\n", nom_fichier);
        exit(EXIT_FAILURE);
    }

    // Lecture des valeurs souhaitées
    for (int i = 0; i < nbSym; i++)
    {
        if (read_uint32(&sym[i].st_name, f, ehdr.e_ident[EI_DATA]) == 0 || read_uint32(&sym[i].st_value, f, ehdr.e_ident[EI_DATA]) == 0 || read_uint32(&sym[i].st_size, f, ehdr.e_ident[EI_DATA]) == 0 || fread(&sym[i].st_info, sizeof(char), 1, f) == 0 || fread(&sym[i].st_other, sizeof(char), 1, f) == 0 || read_uint16(&sym[i].st_shndx, f, ehdr.e_ident[EI_DATA]) == 0)
        {
            fprintf(stderr, "Erreur: %s: Echec de la lecteur du symbole %d\n", nom_fichier, i);
            exit(EXIT_FAILURE);
        }
    }
    fclose(f);
    return sym;
}

void afficher_symboles(Elf32_Sym *sym, char *nom_fichier, char *shstrtab)
{

    FILE *f;
    f = fopen(nom_fichier, "rb");

    if (f == NULL)
    {
        fprintf(stderr, "Impossible d'ouvir le fichier : %s\n", nom_fichier);
        exit(EXIT_FAILURE);
    }

    printf("[Nr]\tValeur\tTaille\tType\tLien\tVisibilite\tNDX\tNom\n");
    for (int i = 0; i < nbSym; i++)
    {
        printf("[%d]\t", i);             // Affichage du numéro du symbole
        printf("%.8x\t", sym[i].st_value); // Affichage de la valeur
        printf("%x\t", sym[i].st_size);  // Affichage de la taille

        switch (ELF32_ST_TYPE(sym[i].st_info)) // Affichage du type
        {
        case STT_NOTYPE:
            printf("Sans\t");
            break;

        case STT_OBJECT:
            printf("Objet\t");
            break;

        case STT_FUNC:
            printf("Fonction\t");
            break;

        case STT_SECTION:
            printf("Section\t");
            break;

        case STT_FILE:
            printf("File\t");
            break;

        case STT_LOPROC:
            printf("Loproc\t");
            break;

        case STT_HIPROC:
            printf("Hiproc\t");
            break;

        default:
            printf("Inconnu\t");
            break;
        }

        switch (ELF32_ST_BIND(sym[i].st_info)) // Affichage du lien
        {
        case STB_LOCAL:
            printf("Local\t");
            break;

        case STB_GLOBAL:
            printf("Global\t");
            break;

        case STB_WEAK:
            printf("Weak\t");
            break;

        case STB_LOPROC:
            printf("Loproc\t");
            break;

        case STB_HIPROC:
            printf("Hiproc\t");
            break;

        default:
            printf("Inconnu\t");
            break;
        }

        switch (ELF32_ST_VISIBILITY(sym[i].st_other)) // Affichage de la visibilité
        {
        case STV_DEFAULT:
            printf("Defaut\t");
            break;

        case STV_INTERNAL:
            printf("Interne\t");
            break;

        case STV_HIDDEN:
            printf("Cache\t");
            break;

        case STV_PROTECTED:
            printf("Protegee\t");
            break;

        default:
            printf("Inconnue\t");
            break;
        }

        printf("%x\t", sym[i].st_shndx); // Affichage du ndx

        // Deplacement au début des symboles
        if (fseek(f, sym[i].st_name, SEEK_SET) != 0)
        {
            fprintf(stderr, "Erreur de lecture du fichier %s\n", nom_fichier);
            exit(EXIT_FAILURE);
        }
        afficher_chaine(shstrtab, sym[i].st_name, 0);
        printf("\n");
    }
}
