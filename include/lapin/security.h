/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file security.h
** This module is about weak security by ciphering.
** It allows you to cipher and uncipher files or buffers with
** a specified key that can also be an internally stored key.
**
** Note that this is not for true security reasons that this
** module is here: the real purpose is to prevent cheating.
**
** Right now, all cipherings algorithms works on the data directly.
** So it size can't be changed.
*/

#ifndef				__LAPIN_SECURITY_H__
# define			__LAPIN_SECURITY_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/**
 * @doc
 * @doc-symbol t_bunny_ciphering
 * @doc-kind enum
 * @doc-module security
 * @doc-order 100
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Lists the weak ciphering algorithms provided by LibLapin.
 * @description These algorithms are meant to hide game or resource data from casual inspection. They are not cryptographic primitives and must not be used as a replacement for a real security library.
 * @description All built-in algorithms transform the buffer in place and keep the same data size.
 * @value BS_XOR Applies XOR between each byte of data and one byte of the key. Applying the same operation twice with the same key restores the original data.
 * @value BS_CAESAR Adds key bytes while ciphering and subtracts them while unciphering.
 * @value BS_SHAKER Swaps bytes according to distances read from the key. The operation is cumulative because each swap changes later swaps.
 * @value BS_SWITCH Encodes bit-state changes instead of bit states. This algorithm does not use the key and is not meant to be used alone.
 * @value BS_BYTBIT Serializes groups of bits between bytes. This algorithm does not use the key.
 * @value BS_BITSHAKE Swaps individual bits according to positions read from the key.
 * @value BS_BITROTATE Rotate layered bit packets
 * @value BS_CUSTOM First value reserved for user-defined algorithms. Any value greater than or equal to it calls gl_bunny_my_cipher or gl_bunny_my_uncipher.
 * @see gl_bunny_ciphering_table, bunny_get_ciphering, bunny_cipher_data, bunny_uncipher_data
 *
 * @doc-lang fr
 * @brief Liste les algorithmes de chiffrement faibles fournis par la LibLapin.
 * @description Ces algorithmes servent à masquer des données de jeu ou des ressources contre une inspection occasionnelle. Ce ne sont pas des primitives cryptographiques et ils ne doivent pas remplacer une vraie bibliothèque de sécurité.
 * @description Tous les algorithmes intégrés transforment le tampon sur place et conservent la même taille de données.
 * @value BS_XOR Applique un XOR entre chaque octet de données et un octet de la clé. Appliquer deux fois la même opération avec la même clé restaure les données originales.
 * @value BS_CAESAR Additionne les octets de la clé pendant le chiffrement et les soustrait pendant le déchiffrement.
 * @value BS_SHAKER Échange des octets selon des distances lues depuis la clé. L'opération est cumulative car chaque échange modifie les échanges suivants.
 * @value BS_SWITCH Encode les changements d'état des bits plutôt que les états eux-mêmes. Cet algorithme n'utilise pas la clé et n'est pas destiné à être utilisé seul.
 * @value BS_BYTBIT Sérialise des groupes de bits entre octets. Cet algorithme n'utilise pas la clé.
 * @value BS_BITSHAKE Échange des bits individuels selon des positions lues depuis la clé.
 * @value BS_BITROTATE Effectue des rotations de bits sur des plages variables
 * @value BS_CUSTOM Première valeur réservée aux algorithmes définis par l'utilisateur. Toute valeur supérieure ou égale appelle gl_bunny_my_cipher ou gl_bunny_my_uncipher.
 * @see gl_bunny_ciphering_table, bunny_get_ciphering, bunny_cipher_data, bunny_uncipher_data
 */
typedef enum			e_bunny_ciphering
  {
    BS_XOR,			/* ^ */
    BS_CAESAR,			/* + */
    BS_SHAKER,			/* swap data in the buffer */
    BS_SWITCH,			/* state bit to switch bit - no key, not meant to be used alone */
    BS_BYTBIT,			/* Serialize bit on bytess - no key */
    BS_BITSHAKE,		/* Like shaker, but on bits */
    BS_BITROTATE,		/* Rotate bits through several nested packet sizes */
    /* BS_1D_TRANSFORM,		Consider the data as a collection of 1D array to be reversed or not */
    /* BS_2D_TRANSFORM,		Consider the data as a collection of 2D arrays to be reversed or rotated */
    /* BS_3D_TRANSFORM,		Consider the data as a collection of 3D arrays to be reversed or rotated */
    /* BS_MIXER,		Reverse N bytes according to key */
    /* BS_COKTAIL		The bunny special: bytes of the key indicates which operation will be done */
    BS_CUSTOM			/* any >= BS_CUSTOM */
  }				t_bunny_ciphering;

/**
 * @doc
 * @doc-symbol gl_bunny_ciphering_table
 * @doc-kind variable
 * @doc-module security
 * @doc-order 120
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Associates built-in ciphering algorithms with their textual names.
 * @description The table contains one name for each built-in value before BS_CUSTOM. bunny_get_ciphering reads this table to resolve names such as "xor", "caesar", "shaker", "switch", "bytbit" and "bitshake".
 * @see t_bunny_ciphering, bunny_get_ciphering
 *
 * @doc-lang fr
 * @brief Associe les algorithmes de chiffrement intégrés à leurs noms textuels.
 * @description Le tableau contient un nom pour chaque valeur intégrée avant BS_CUSTOM. bunny_get_ciphering lit ce tableau pour résoudre des noms comme "xor", "caesar", "shaker", "switch", "bytbit" et "bitshake".
 * @see t_bunny_ciphering, bunny_get_ciphering
 */
extern const char * const	gl_bunny_ciphering_table[BS_CUSTOM];

t_bunny_ciphering		bunny_get_ciphering(const char			*name);

/**
 * @doc
 * @doc-symbol t_bunny_cipher_key
 * @doc-kind type
 * @doc-module security
 * @doc-order 160
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Represents a ciphering key.
 * @description The key stores a byte length followed by a flexible byte array. The bytes are raw key data, not a null-terminated string.
 * @description To allocate a key manually, reserve sizeof(t_bunny_cipher_key) plus the wanted number of key bytes, then set length and fill key. bunny_new_key does this for you.
 * @field length Length of key in bytes.
 * @field key Raw bytes used by the ciphering algorithms.
 * @see bunny_new_key, bunny_delete_key, bunny_default_key
 *
 * @doc-lang fr
 * @brief Représente une clé de chiffrement.
 * @description La clé stocke une longueur en octets suivie d'un tableau flexible d'octets. Ces octets sont des données de clé brutes, pas une chaîne terminée par zéro.
 * @description Pour allouer une clé manuellement, réservez sizeof(t_bunny_cipher_key) plus le nombre d'octets souhaité, puis renseignez length et key. bunny_new_key le fait pour vous.
 * @field length Longueur de key en octets.
 * @field key Octets bruts utilisés par les algorithmes de chiffrement.
 * @see bunny_new_key, bunny_delete_key, bunny_default_key
 */
typedef struct			s_bunny_cipher_key
{
  int32_t			length;
  char				key[__ZERO_LENGTH__];
}				t_bunny_cipher_key;

const t_bunny_cipher_key	*bunny_default_key(void);

bool				bunny_fill_default_key(const char	*bunny_program,
					       const t_bunny_cipher_key *key);

/**
 * @doc
 * @doc-symbol t_bunny_key_twist
 * @doc-kind type
 * @doc-module security
 * @doc-order 220
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Defines the callback type used to derive a runtime key from the embedded key.
 * @description bunny_default_key uses gl_bunny_my_key_twist, when set, to transform the embedded key before returning it. The callback must be deterministic: the same embedded key must always produce the same runtime key.
 * @param inkey The original embedded key.
 * @param outkey The storage in which the transformed key must be written.
 * @return-success outkey after it has been filled.
 * @see gl_bunny_my_key_twist, bunny_default_key
 *
 * @doc-lang fr
 * @brief Définit le type de callback utilisé pour dériver une clé d'exécution depuis la clé embarquée.
 * @description bunny_default_key utilise gl_bunny_my_key_twist, lorsqu'il est renseigné, pour transformer la clé embarquée avant de la renvoyer. Le callback doit être déterministe : la même clé embarquée doit toujours produire la même clé d'exécution.
 * @param inkey La clé embarquée originale.
 * @param outkey L'espace dans lequel la clé transformée doit être écrite.
 * @return-success outkey après remplissage.
 * @see gl_bunny_my_key_twist, bunny_default_key
 */
typedef t_bunny_cipher_key	*(*t_bunny_key_twist)(const t_bunny_cipher_key	*inkey,
						      t_bunny_cipher_key	*outkey);

/**
 * @doc
 * @doc-symbol gl_bunny_my_key_twist
 * @doc-kind variable
 * @doc-module security
 * @doc-order 240
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Stores the key-twist callback used by bunny_default_key.
 * @description When this pointer is NULL, bunny_default_key uses the built-in transformation. When it is set, the pointed function is responsible for producing the runtime key from the embedded key.
 * @see t_bunny_key_twist, bunny_default_key
 *
 * @doc-lang fr
 * @brief Stocke le callback de transformation de clé utilisé par bunny_default_key.
 * @description Lorsque ce pointeur vaut NULL, bunny_default_key utilise la transformation intégrée. Lorsqu'il est renseigné, la fonction pointée doit produire la clé d'exécution à partir de la clé embarquée.
 * @see t_bunny_key_twist, bunny_default_key
 */
extern t_bunny_key_twist	gl_bunny_my_key_twist;

t_bunny_cipher_key		*bunny_new_key(size_t				len);

void				bunny_delete_key(t_bunny_cipher_key		*key);

bool				bunny_cipher_file(const char			*file,
						  t_bunny_ciphering		ciphering,
						  const t_bunny_cipher_key	*key);

bool				bunny_uncipher_file(const char			*file,
						    t_bunny_ciphering		ciphering,
						    const t_bunny_cipher_key	*key);

void				bunny_cipher_data(void				*data,
						  size_t			datalen,
						  t_bunny_ciphering		ciphering,
						  const t_bunny_cipher_key	*key);

void				bunny_uncipher_data(void			*data,
						    size_t			data_len,
						    t_bunny_ciphering		ciphering,
						    const t_bunny_cipher_key	*key);

/**
 * @doc
 * @doc-symbol t_bunny_my_cipher
 * @doc-kind type
 * @doc-module security
 * @doc-order 380
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Defines the callback type used for custom ciphering algorithms.
 * @description bunny_cipher_file and bunny_cipher_data call gl_bunny_my_cipher when the requested algorithm is BS_CUSTOM or any greater value. The callback modifies buffer in place.
 * @param ciphering The custom algorithm identifier sent to the ciphering function.
 * @param buffer The buffer to cipher.
 * @param len The length of buffer in bytes.
 * @param key The key passed to the ciphering function.
 * @see gl_bunny_my_cipher, t_bunny_my_uncipher, bunny_cipher_data, bunny_cipher_file
 *
 * @doc-lang fr
 * @brief Définit le type de callback utilisé pour les algorithmes de chiffrement personnalisés.
 * @description bunny_cipher_file et bunny_cipher_data appellent gl_bunny_my_cipher lorsque l'algorithme demandé vaut BS_CUSTOM ou une valeur supérieure. Le callback modifie buffer sur place.
 * @param ciphering L'identifiant d'algorithme personnalisé envoyé à la fonction de chiffrement.
 * @param buffer Le tampon à chiffrer.
 * @param len La longueur de buffer en octets.
 * @param key La clé transmise à la fonction de chiffrement.
 * @see gl_bunny_my_cipher, t_bunny_my_uncipher, bunny_cipher_data, bunny_cipher_file
 */
typedef void			(*t_bunny_my_cipher)(t_bunny_ciphering		ciphering,
						     char			*buffer,
						     size_t			len,
						     const t_bunny_cipher_key	*key);

/**
 * @doc
 * @doc-symbol gl_bunny_my_cipher
 * @doc-kind variable
 * @doc-module security
 * @doc-order 400
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Stores the callback used by ciphering functions for custom algorithms.
 * @description Set this pointer before calling bunny_cipher_file or bunny_cipher_data with BS_CUSTOM or any greater value. If it is NULL when such an algorithm is used, the call is invalid.
 * @see t_bunny_my_cipher, gl_bunny_my_uncipher, bunny_cipher_data, bunny_cipher_file
 *
 * @doc-lang fr
 * @brief Stocke le callback utilisé par les fonctions de chiffrement pour les algorithmes personnalisés.
 * @description Affectez ce pointeur avant d'appeler bunny_cipher_file ou bunny_cipher_data avec BS_CUSTOM ou une valeur supérieure. S'il vaut NULL lorsqu'un tel algorithme est utilisé, l'appel est invalide.
 * @see t_bunny_my_cipher, gl_bunny_my_uncipher, bunny_cipher_data, bunny_cipher_file
 */
extern t_bunny_my_cipher	gl_bunny_my_cipher;

/**
 * @doc
 * @doc-symbol t_bunny_my_uncipher
 * @doc-kind type
 * @doc-module security
 * @doc-order 420
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Defines the callback type used for custom unciphering algorithms.
 * @description bunny_uncipher_file and bunny_uncipher_data call gl_bunny_my_uncipher when the requested algorithm is BS_CUSTOM or any greater value. The callback modifies buffer in place.
 * @param ciphering The custom algorithm identifier sent to the unciphering function.
 * @param buffer The buffer to uncipher.
 * @param len The length of buffer in bytes.
 * @param key The key passed to the unciphering function.
 * @see gl_bunny_my_uncipher, t_bunny_my_cipher, bunny_uncipher_data, bunny_uncipher_file
 *
 * @doc-lang fr
 * @brief Définit le type de callback utilisé pour les algorithmes de déchiffrement personnalisés.
 * @description bunny_uncipher_file et bunny_uncipher_data appellent gl_bunny_my_uncipher lorsque l'algorithme demandé vaut BS_CUSTOM ou une valeur supérieure. Le callback modifie buffer sur place.
 * @param ciphering L'identifiant d'algorithme personnalisé envoyé à la fonction de déchiffrement.
 * @param buffer Le tampon à déchiffrer.
 * @param len La longueur de buffer en octets.
 * @param key La clé transmise à la fonction de déchiffrement.
 * @see gl_bunny_my_uncipher, t_bunny_my_cipher, bunny_uncipher_data, bunny_uncipher_file
 */
typedef void			(*t_bunny_my_uncipher)(t_bunny_ciphering	ciphering,
						       char			*buffer,
						       size_t			len,
						       const t_bunny_cipher_key	*key);

/**
 * @doc
 * @doc-symbol gl_bunny_my_uncipher
 * @doc-kind variable
 * @doc-module security
 * @doc-order 440
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Stores the callback used by unciphering functions for custom algorithms.
 * @description Set this pointer before calling bunny_uncipher_file or bunny_uncipher_data with BS_CUSTOM or any greater value. If it is NULL when such an algorithm is used, the call is invalid.
 * @see t_bunny_my_uncipher, gl_bunny_my_cipher, bunny_uncipher_data, bunny_uncipher_file
 *
 * @doc-lang fr
 * @brief Stocke le callback utilisé par les fonctions de déchiffrement pour les algorithmes personnalisés.
 * @description Affectez ce pointeur avant d'appeler bunny_uncipher_file ou bunny_uncipher_data avec BS_CUSTOM ou une valeur supérieure. S'il vaut NULL lorsqu'un tel algorithme est utilisé, l'appel est invalide.
 * @see t_bunny_my_uncipher, gl_bunny_my_cipher, bunny_uncipher_data, bunny_uncipher_file
 */
extern t_bunny_my_uncipher	gl_bunny_my_uncipher;

/**
 * @doc
 * @doc-symbol t_bunny_ressource_cipher
 * @doc-kind type
 * @doc-module security
 * @doc-order 460
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Defines the callback type used to cipher or uncipher resources during loading and saving.
 * @description Resource loading and saving functions can use gl_bunny_ressource_ciphering to transform file content automatically. The callback modifies buffer in place.
 * @param buffer The data to cipher or uncipher.
 * @param len The length of buffer in bytes.
 * @param data The user data stored in gl_bunny_ressource_data.
 * @param cipher true when ciphering, false when unciphering.
 * @see gl_bunny_ressource_ciphering, gl_bunny_ressource_data
 *
 * @doc-lang fr
 * @brief Définit le type de callback utilisé pour chiffrer ou déchiffrer les ressources pendant leur chargement et leur sauvegarde.
 * @description Les fonctions de chargement et de sauvegarde de ressources peuvent utiliser gl_bunny_ressource_ciphering pour transformer automatiquement le contenu des fichiers. Le callback modifie buffer sur place.
 * @param buffer Les données à chiffrer ou déchiffrer.
 * @param len La longueur de buffer en octets.
 * @param data Les données utilisateur stockées dans gl_bunny_ressource_data.
 * @param cipher true pour chiffrer, false pour déchiffrer.
 * @see gl_bunny_ressource_ciphering, gl_bunny_ressource_data
 */
typedef void			(*t_bunny_ressource_cipher)(char		*buffer,
							    size_t		len,
							    void		*data,
							    bool		cipher);

/**
 * @doc
 * @doc-symbol gl_bunny_ressource_ciphering
 * @doc-kind variable
 * @doc-module security
 * @doc-order 480
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Stores the callback used to cipher or uncipher resources during loading and saving.
 * @description The pointer is NULL by default. When it is set, compatible resource loading functions call it to uncipher loaded content, and compatible saving functions call it to cipher saved content.
 * @see t_bunny_ressource_cipher, gl_bunny_ressource_data
 *
 * @doc-lang fr
 * @brief Stocke le callback utilisé pour chiffrer ou déchiffrer les ressources pendant leur chargement et leur sauvegarde.
 * @description Le pointeur vaut NULL par défaut. Lorsqu'il est renseigné, les fonctions de chargement compatibles l'appellent pour déchiffrer le contenu chargé, et les fonctions de sauvegarde compatibles l'appellent pour chiffrer le contenu sauvegardé.
 * @see t_bunny_ressource_cipher, gl_bunny_ressource_data
 */
extern t_bunny_ressource_cipher gl_bunny_ressource_ciphering;

/**
 * @doc
 * @doc-symbol gl_bunny_ressource_data
 * @doc-kind variable
 * @doc-module security
 * @doc-order 500
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Stores the user pointer passed to gl_bunny_ressource_ciphering.
 * @description This pointer is transmitted as the data parameter of the resource ciphering callback. It is NULL by default and is never interpreted by LibLapin.
 * @see t_bunny_ressource_cipher, gl_bunny_ressource_ciphering
 *
 * @doc-lang fr
 * @brief Stocke le pointeur utilisateur transmis à gl_bunny_ressource_ciphering.
 * @description Ce pointeur est transmis comme paramètre data du callback de chiffrement de ressources. Il vaut NULL par défaut et n'est jamais interprété par la LibLapin.
 * @see t_bunny_ressource_cipher, gl_bunny_ressource_ciphering
 */
extern void			*gl_bunny_ressource_data;

#endif	/*			__LAPIN_SECURITY_H__			*/
