#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* TOUT CECI SORT DE LA DOCUMENTATION DE L'ENTETE D'UN FICHIER ELF */

// Redéfinie plus bas
#define EI_NIDENT 16

/* ELF32 types de base en 32-bit */
typedef uint32_t Elf32_Addr;
typedef uint16_t Elf32_Half;
typedef uint32_t Elf32_Off;
typedef uint32_t Elf32_Word;

/* ELF32 Structure de l'entête en 32-bit */
typedef struct
{
    unsigned char e_ident[EI_NIDENT];
    Elf32_Half e_type;
    Elf32_Half e_machine;
    Elf32_Word e_version;
    Elf32_Addr e_entry;
    Elf32_Off e_phoff;
    Elf32_Off e_shoff;
    Elf32_Word e_flags;
    Elf32_Half e_ehsize;
    Elf32_Half e_phentsize;
    Elf32_Half e_phnum;
    Elf32_Half e_shentsize;
    Elf32_Half e_shnum;
    Elf32_Half e_shstrndx;
} Elf32_Ehdr;

/* e_ident */
// e_ident est un tableau dont chaque indice possède une certaine valeure
#define EI_MAG0 0 /* File identification */                  // Contient la valeur : 0x7f
#define EI_MAG1 1 /* File identification */                  // Contient la valeur : 'E'
#define EI_MAG2 2 /* File identification */                  // Contient la valeur : 'L'
#define EI_MAG3 3 /* File identification */                  // Contient la valeur : 'F'
#define EI_CLASS 4 /* File class */                          // Contient la valeur : 0 Si correspond à ELFCLASSNONE donc Invalid class
                                                             // Contient la valeur : 1 Si correspond à ELFCLASS32 donc 32-bit objects
                                                             // Contient la valeur : 2 Si correspond à ELFCLASS64 donc 64-bit objects
#define EI_DATA 5 /* Data encoding */                        // Contient la valeur : 0 Si correspond à ELFDATANONE donc Invalid data encoding
                                                             // Contient la valeur : 1 Si correspond à ELFDATA2LSB donc byte address zero on the left : 04 03 02 01 = 0x 01020304 Little Endian
                                                             // Contient la valeur : 2 Si correspond à ELFDATA2MSB donc byte address zero on the left : 01 02 03 04 = 0x 01020304 Big Endian
#define EI_VERSION 6 /* File version */                      // Souvent égale à EV_CURRENT
#define EI_OSABI 7 /* Operating system/ABI identification */ // Contient la valeur : 0  Si correspond à ELFOSABI_NONE donc No extensions or unspecified
                                                             // Contient la valeur : 1  Si correspond à ELFOSABI_HPUX donc Hewlett-Packard HP-UX
                                                             // Contient la valeur : 2  Si correspond à ELFOSABI_NETBSD donc NetBSD
                                                             // Contient la valeur : 3  Si correspond à ELFOSABI_GNU donc GNU
                                                             // Contient la valeur : 3  Si correspond à ELFOSABI_LINUX  donc Linux
                                                             // Contient la valeur : 6  Si correspond à ELFOSABI_SOLARIS donc Sun Solaris
                                                             // Contient la valeur : 7  Si correspond à ELFOSABI_AIX donc AIX
                                                             // Contient la valeur : 8  Si correspond à ELFOSABI_IRIX donc IRIX
                                                             // Contient la valeur : 9  Si correspond à ELFOSABI_FREEBSD donc FreeBSD
                                                             // Contient la valeur : 10 Si correspond à ELFOSABI_TRU64 donc Compaq TRU64 UNIX
                                                             // Contient la valeur : 11 Si correspond à ELFOSABI_MODESTO donc Novell Modesto
                                                             // Contient la valeur : 12 Si correspond à ELFOSABI_OPENBSD donc Open BSD
                                                             // Contient la valeur : 13 Si correspond à ELFOSABI_OPENVMS donc Open VMS
                                                             // Contient la valeur : 14 Si correspond à ELFOSABI_NSK  donc Hewlett-Packard Non-Stop Kernel
                                                             // Contient la valeur : 15 Si correspond à ELFOSABI_AROS donc Amiga Research OS
                                                             // Contient la valeur : 16 Si correspond à ELFOSABI_FENIXOS donc The FenixOS highly scalable multi-core OS
                                                             // Contient la valeur : 17 Si correspond à ELFOSABI_CLOUDABI donc Nuxi CloudABI
                                                             // Contient la valeur : 18 Si correspond à ELFOSABI_OPENVOS donc Stratus Technologies OpenVOS
                                                             // Contient la valeur : 64-255 Si correspond à Architecture-specific value range
#define EI_ABIVERSION 8 /* ABI version */                    // Dépend du champ EI_OSABI
                                                             // Contient la valeur : 0 Si aucune valeur pour EI_OSABI par le supplément processeur ou si aucune valeur de version spécifiée pour une valeur particulière de l'octet EI_OSABI Donc indiqué comme non spécifié.
#define EI_PAD 9 /* Start of padding bytes */                // Début des octets inutilisés dans e_ident (Ces octets sont réservés et mis à zéro, Les programmes qui lisent les fichiers d'objets doivent les ignorer)
                                                             // Cet valeur changera dans le futur si l'on donne une signification aux octets actuellement inutilisés
#define EI_NIDENT 16 /* Size of e_ident[] */                 // Contient la taille du tableau e_ident[]

/* EI_MAG0 à EI_MAG3 */
#define ELFMAG0 0x7f     /* e_ident[EI_MAG0] */
#define ELFMAG1 'E'      /* e_ident[EI_MAG1] */
#define ELFMAG2 'L'      /* e_ident[EI_MAG2] */
#define ELFMAG3 'F'      /* e_ident[EI_MAG3] */
#define ELFMAG "\177ELF" /* Identifiant ELF complet en string */
#define SELFMAG 4        /* Taille de l'identifiant ELF */

/* EI_CLASS */
#define ELFCLASSNONE 0 /* Invalid class */
#define ELFCLASS32 1   /* 32-bit objects */
#define ELFCLASS64 2   /* 64-bit objects */

/* EI_DATA */
#define ELFDATANONE 0 /* Invalid data encoding */
#define ELFDATA2LSB 1 /* Little Endian */
#define ELFDATA2MSB 2 /* Big Endian */

/* EI_OSABI */
#define ELFOSABI_NONE 0      /* No extensions or unspecified */
#define ELFOSABI_HPUX 1      /* Hewlett-Packard HP-UX */
#define ELFOSABI_NETBSD 2    /* NetBSD */
#define ELFOSABI_GNU 3       /* GNU */
#define ELFOSABI_LINUX 3     /* Linux  */
#define ELFOSABI_SOLARIS 6   /* Sun Solaris */
#define ELFOSABI_AIX 7       /* AIX */
#define ELFOSABI_IRIX 8      /* IRIX */
#define ELFOSABI_FREEBSD 9   /* FreeBSD */
#define ELFOSABI_TRU64 10    /* Compaq TRU64 UNIX */
#define ELFOSABI_MODESTO 11  /* Novell Modesto */
#define ELFOSABI_OPENBSD 12  /* Open BSD */
#define ELFOSABI_OPENVMS 13  /* Open VMS */
#define ELFOSABI_NSK 14      /* Hewlett-Packard Non-Stop Kernel */
#define ELFOSABI_AROS 15     /* Amiga Research OS */
#define ELFOSABI_FENIXOS 16  /* The FenixOS highly scalable multi-core OS */
#define ELFOSABI_CLOUDABI 17 /* Nuxi CloudABI */
#define ELFOSABI_OPENVOS 18  /* Stratus Technologies OpenVOS */

/* e_type */
#define ET_NONE 0        /* No file type */
#define ET_REL 1         /* Relocatable file */
#define ET_EXEC 2        /* Executable file */
#define ET_DYN 3         /* Shared object file */
#define ET_CORE 4        /* Core file */
#define ET_LOOS 0xfe00   /* Operating system-specific */
#define ET_HIOS 0xfeff   /* Operating system-specific */
#define ET_LOPROC 0xff00 /* Processor-specific */
#define ET_HIPROC 0xffff /* Processor-specific */

/* e_machine */
#define EM_NONE 0         /* No machine */
#define EM_M32 1          /* AT&T WE 32100 */
#define EM_SPARC 2        /* SPARC */
#define EM_386 3          /* Intel Architecture */
#define EM_68K 4          /* Motorola 68000 */
#define EM_88K 5          /* Motorola 88000 */
#define EM_IAMCU 6        /* Intel MCU */
#define EM_860 7          /* Intel 80860 */
#define EM_MIPS 8         /* MIPS RS3000 Big-Endian */
#define EM_S370 9         /* IBM System/370 Processor */
#define EM_MIPS_RS4_BE 10 /* MIPS RS4000 Big-Endian */
//      RESERVED        11-16   Reserved for future use
//      RESERVED        17-39   Other Machine
#define EM_ARM 40 /* ARM 32-bit architecture (AARCH32) */
//      RESERVED        41-243  Other Machine

/* e_version */
#define EV_NONE 0    /* Invalid version */
#define EV_CURRENT 1 /* Current version */

/* e_entry */

/* e_phoff */

/* e_shoff */

/* e_flags */

/* e_ehsize */

/* e_phentsize */

/* e_phnum */

/* e_shentsize */

/* e_shnum */

/* e_shstrndx */

int bigToLittle(int big) {

    int bigEndian = big;
    int little = (((big & 0xff)<<8) | ((big & 0xff00)>>8));
    return little;

}

int main(int argc, char const *argv[])
{
    FILE *fic;
    Elf32_Ehdr elf32;

    fic = fopen("example1.o", "rb");

    if (fic == NULL)
    {
        fprintf(stderr, "Erreur d'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }

    printf("ELF Header:\n");

    fread(&elf32, sizeof(elf32), 1, fic);

    /* Magic */
    printf("  Magic:   %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x\n", elf32.e_ident[0], elf32.e_ident[1], elf32.e_ident[2], elf32.e_ident[3], elf32.e_ident[4], elf32.e_ident[5], elf32.e_ident[6], elf32.e_ident[7], elf32.e_ident[8], elf32.e_ident[9], elf32.e_ident[10], elf32.e_ident[11], elf32.e_ident[12], elf32.e_ident[13], elf32.e_ident[14], elf32.e_ident[15]);
    
    /* Class */
    printf("  Class:\t\t\t\t");
    switch (elf32.e_ident[4])
    {
    case 0:
        printf("Invalid class\n");
        break;

    case 1:
        printf("ELF32\n");
        break;

    case 2:
        printf("ELF64\n");
        break;
    
    default:
        break;
    }

    /* Data */
    printf("  Data:\t\t\t\t");
    switch (elf32.e_ident[5])
    {
    case 0:
        printf("\tInvalid data encoding\n");
        break;

    case 1:
        printf("\tLittle endian\n");
        break;

    case 2:
        printf("\tBig endian\n");
        break;
    
    default:
        break;
    }

    /* Version */
    printf("  Version:\t\t\t");
    switch (elf32.e_ident[6])
    {
    case 0:
        printf("\t%d (Invalid)\n", elf32.e_ident[6]);
        break;

    case 1:
        printf("\t%d (Current)\n", elf32.e_ident[6]);
        break;
    
    default:
        break;
    }

    /* OS/ABI */
    printf("  OS/ABI:\t\t\t\t"); 
    switch (elf32.e_ident[7])
    {
    case 0:
        printf("No extensions or unspecified\n");
        break;

    case 1:
        printf("Hewlett-Packard HP-UX\n");
        break;

    case 2:
        printf("NetBSD\n");
        break;
    
    case 3:
        printf("GNU - Linux\n");
        break;
    
    case 6:
        printf("Sun Solaris\n");
        break;

    case 7:
        printf("AIX\n");
        break;

    case 8:
        printf("IRIX\n");
        break;

    case 9:
        printf("FreeBSD\n");
        break;
    
    case 10:
        printf("Compaq TRU64 UNIX\n");
        break;
    
    case 11:
        printf("Novell Modesto\n");
        break;

    case 12:
        printf("Open BSD\n");
        break;

    case 13:
        printf("Open VMS\n");
        break;

    case 14:
        printf("Hewlett-Packard Non-Stop Kernel\n");
        break;
    
    case 15:
        printf("Amiga Research OS\n");
        break;
    
    case 16:
        printf("The FenixOS highly scalable multi-core OS\n");
        break;
    
    case 17:
        printf("Nuxi CloudABI\n");
        break;
        
    case 18:
        printf("Stratus Technologies OpenVOS\n");
        break;
    
    default:
        printf("Architecture-specific value range\n");
        break;
    }

    /* ABI Version */
    printf("  ABI Version:\t\t\t\t%d\n", elf32.e_ident[8]);

    /* Type */
    printf("  Type:\t\t\t\t\t");
    switch (bigToLittle(elf32.e_type))
    {
    case 0:
        printf("No file type\n");
        break;

    case 1:
        printf("Relocatable file\n");
        break;

    case 2:
        printf("Executable file\n");
        break;

    case 3:
        printf("Shared object file\n");
        break;
    
    case 4:
        printf("Core file\n");
        break;

    case 0xfe00:
        printf("Operating system-specific\n");
        break;

    case 0xfeff:
        printf("Operating system-specific\n");
        break;

    case 0xff00:
        printf("Processor-specific\n");
        break;

    case 0xffff:
        printf("Processor-specific\n");
        break;

    default:
        printf("val: %4x\n", elf32.e_type);
        break;
    }

    /* Machine */
    printf("  Machine:\t\t\t");
    switch (bigToLittle(elf32.e_machine))
    {
    case 0:
        printf("No machine\n");
        break;

    case 1:
        printf("\tAT&T WE 32100\n");
        break;

    case 2:
        printf("\tSPARC\n");
        break;

    case 3:
        printf("\tIntel Architecture\n");
        break;
    
    case 4:
        printf("\tMotorola 68000\n");
        break;
    
    case 5:
        printf("\tMotorola 88000\n");
        break;

    case 6:
        printf("\tIntel MCU\n");
        break;

    case 7:
        printf("\tIntel 80860\n");
        break;

    case 8:
        printf("\tMIPS RS3000 Big-Endian\n");
        break;
    
    case 9:
        printf("\tIBM System/370 Processor\n");
        break;

    case 10:
        printf("\tMIPS RS4000 Big-Endian\n");
        break;
    
    case 40:
        printf("\tARM 32-bit architecture (AARCH32)\n");
        break;
    
    default:
        printf("\tOther Machine\n");
        break;
    }

    /* Version */
    printf("  Version:\t\t\t\t0x%1x\n", bigToLittle(elf32.e_version));
    printf("Test1: %x", elf32.e_version); 
    printf("Test1: %x", bigToLittle(elf32.e_version));    

// TO DO !!!!!!!!!!!!!!!!!!!!!!!

    /* Entry point address */
    printf("  Entry point address:\t\t\t0x%1x\n", bigToLittle(elf32.e_entry));

    /* AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA */
    /* Start of program headers */
    printf("  Start of program headers:\t\t%d\n", elf32.e_phoff);

    /* Start of section headers */
    printf("  Start of section headers:\t\t%d\n", elf32.e_shoff);

    /* Flags */
    printf("  Flags:\t\t\t\t0x%1.7x\n", elf32.e_flags);


    printf("  Size of this header:\t\t%d\n", elf32.e_ehsize);

    printf("  Size of program headers:\t\t%d\n", elf32.e_phentsize);

    printf("  Number of program headers:\t\t%d\n", elf32.e_phnum);

    printf("  Size of section headers:\t\t%d\n", elf32.e_shentsize);

    printf("  Number of section headers:\t\t%d\n", elf32.e_shnum);

    printf("  Section header string table index:\t%d\n", elf32.e_shstrndx);

    return 0;
}
