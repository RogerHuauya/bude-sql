<a name="readme-top"></a>
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]


<br />
<div align="center">  
  <a href="https://github.com/RogerHuauya/bude-sql"> <!-- URL DEL REPO-->
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">Bude-SQL</h3>

  <p align="center">
    Un proyecto en C++ que integra métodos personalizados de indexación de bases de datos con una interfaz gráfica utilizando RayLib.
    <br />
    <a href="https://github.com/RogerHuauya/bude-sql"><strong>Explora el documento</strong></a>
    <br />
    <br />
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Tabla de contenidos</summary>
  <ol>
    <li>
      <a href="#about-the-project">Sobre el proyecto</a>
      <ul>
        <li><a href="#built-with">Construido con </a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisitos</a></li>
        <li><a href="#installation">Instalación</a></li>
      </ul>
    </li>
    <li><a href="#usage">Uso</a></li>
    <li><a href="#contact">Miembros</a></li>
    <li><a href="#acknowledgments">Agradecimientos</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

<!-- [![Product Name Screen Shot][product-screenshot]](https://example.com) -->

**Bude-SQL** es un sistema de gestión de bases de datos desarrollado en C++, que utiliza métodos de indexación avanzados como AVL, B+ Trees y Extendible Hash para optimizar las consultas. Este proyecto combina teoría y práctica mediante la implementación de estas estructuras en un entorno real, acompañado de una interfaz gráfica desarrollada con RayLib.

### Objetivos del Proyecto

- **Implementar Estructuras de Datos Avanzadas**: Enseñar la implementación y uso de AVL, B+ Trees y Extendible Hash en bases de datos.
- **Herramienta Educativa y Práctica**: Servir como recurso educativo y práctico para estudiantes y profesionales interesados en bases de datos y programación en C++.
- **Interfaz Gráfica Intuitiva**: Facilitar la manipulación visual de las estructuras de datos gracias a RayLib.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With

* [![C++][C++-img]][C++-url]
* [![Raylib][Raylib-img]][Raylib-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

Para poner en marcha una copia local, siga estos sencillos pasos.

### Prerequisites

Prerequisitos

### Installation

Instalación

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage

La estructura AppRecord es utilizada para almacenar información sobre aplicaciones de la IStore, detallada en un archivo CSV llamado Apple.csv. Cada parte de la estructura representa un campo específico relacionado con las aplicaciones:

* id: Es un entero sin signo que actúa como identificador único para cada aplicación. Este número es probablemente asignado secuencialmente y es único para cada app en la base de datos.

* app_name: Es un arreglo de caracteres con capacidad para 256 caracteres incluyendo el carácter nulo al final. Almacena el nombre de la aplicación.

* size_bytes: Un entero sin signo que indica el tamaño de la aplicación en bytes. Esto puede ser útil para los usuarios que consideren el espacio de almacenamiento antes de descargar una aplicación.

* price: Un número de punto flotante que representa el precio de la aplicación en la tienda. Si el precio es 0.0, esto normalmente indica que la aplicación es gratuita.

* rating_count_tot: Un entero sin signo que representa el número total de valoraciones que ha recibido la aplicación. Este número puede ser un indicador de la popularidad o la aceptación de la aplicación entre los usuarios.

* user_rating: Un enumerado UserRating que representa la valoración promedio dada por los usuarios a la aplicación. Este tipo enumerado podría estar definido en otra parte del código, proporcionando una escala específica para las valoraciones (como 0 a 5, con posibilidad de medias estrellas).

* cont_rating: Un arreglo de caracteres con capacidad para 4 caracteres. Almacena la clasificación de contenido de la aplicación, indicando para qué grupo de edad es apropiada la aplicación, como "4+", "12+", etc.

* prime_genre: Un arreglo de caracteres que puede contener hasta 18 caracteres. Representa el género principal de la aplicación, como "Juegos", "Educación", "Negocios", etc.

* removed: Un valor booleano que indica si la aplicación ha sido retirada de la tienda. Esto puede ser útil para filtrar o realizar análisis en las aplicaciones que aún están disponibles.
```{c++}
struct AppRecord {
    unsigned int id{};
    char app_name[256]{'\0'};
    unsigned int size_bytes;
    float price{};
    unsigned int rating_count_tot{};
    UserRating user_rating{};
    char cont_rating[4]{'\0'};
    char prime_genre[18]{'\0'};
    bool removed{};
};
```
La información necesaria es transformada luego a un archivo Apple.dat en formato binario para un mejor manejo de las consultas.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->
## Contact

| Name            | Email                     | GitHub User    |
|-----------------|---------------------------|----------------|
| Roger Huauya Mamani | roger.huauya@utec.edu.pe | [Rogerhuauya](https://github.com/Rogerhuauya) |
| Arturo Barrantes | arturo.barrantes@utec.edu.pe | [Arturo Barrantes](https://github.com/xkal1bur) |
| Rodrigo León | rodrigo.leon@utec.edu.pe | [RodrigoLeonUTEC](https://github.com/RodrigoLeonUTEC) |
| Angelo Sodli | angello.soldi@utec.edu.pe | [darkblackv32](https://github.com/darkblackv32) |
| .... | ....@utec.edu.pe | [...](https://github.com/xkal1bur) |


<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* [Heider Sanchez](https://github.com/heidersanchez)

<p align="right">(<a href="#readme-top">Volver al inicio</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/RogerHuauya/bude-sql.svg?style=for-the-badge
[contributors-url]: https://github.com/RogerHuauya/bude-sql/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/RogerHuauya/bude-sql.svg?style=for-the-badge
[forks-url]: https://github.com/RogerHuauya/bude-sql/network/members
[stars-shield]: https://img.shields.io/github/stars/RogerHuauya/bude-sql.svg?style=for-the-badge
[stars-url]: https://github.com/RogerHuauya/bude-sql/stargaz
[product-screenshot]: images/logo.webp
[Raylib-url]: https://www.raylib.com/
[Raylib-img]: https://img.shields.io/badge/Raylib-000000?style=for-the-badge&logo=raylib&logoColor=white
[C++-url]: https://isocpp.org/
[C++-img]: https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white
