# 🪖 Command & Conquer: Red Alert (1996) — Port Nativo para iPadOS

[![Platform](https://img.shields.io/badge/Platform-iPadOS%2016%2B%20%7C%20macOS%2012%2B%20%7C%20Linux%20%7C%20Android-blue.svg)](https://github.com/MargeLenders/redalert-ipad)
[![Architecture](https://img.shields.io/badge/Architecture-ARM64%20(Apple%20Silicon)%20%7C%20x86__64-orange.svg)](https://github.com/MargeLenders/redalert-ipad)
[![Upstream](https://img.shields.io/badge/Upstream-Fork%20de%20dk8827%2Fra--port-brightgreen.svg)](https://github.com/dk8827/ra-port)
[![Graphics](https://img.shields.io/badge/Graphics-SDL2%20Hardware%20Accelerated-green.svg)](https://www.libsdl.org/)
[![Audio](https://img.shields.io/badge/Audio-DirectSound%20Shim%20%2F%20SDL2%20Audio-purple.svg)](https://www.libsdl.org/)
[![License](https://img.shields.io/badge/License-GPLv3%20con%20t%C3%A9rminos%20adicionales-lightgrey.svg)](LICENSE.md)

Port nativo de alto rendimiento del mítico juego de estrategia en tiempo real **Command & Conquer: Red Alert (Westwood Studios, 1996)**, ejecutándose directamente sobre **iPadOS (iPad)**.

Este proyecto es un fork de [`dk8827/ra-port`](https://github.com/dk8827/ra-port), el cual modernizó la base de código original en C++ liberada por Electronic Arts bajo licencia GPLv3 (<https://github.com/electronicarts/CnC_Red_Alert>).

Este fork transforma el port en una experiencia táctil de primer nivel con **soporte nativo para iPadOS 16+**, un **HUD táctil retro estilo Westwood (1996)**, **gestos multitoque 1:1**, icono retro soviético y herramientas automatizadas para compilar tanto en el simulador como en un iPad real.

---

## ✨ Características Principales

* **🎮 Control Táctil Directo 1:1 y HUD Táctico (Sin mandos virtuales toscos)**:
  * **Toque con 1 dedo**: Seleccionar unidades, ordenar movimiento/ataque, colocar edificios y usar la barra lateral de producción.
  * **Arrastre con 1 dedo (Selección en caja)**: Caja de selección verde (*rubber-band*) para seleccionar múltiples unidades a la vez.
  * **Toque con 2 dedos**: Clic derecho nativo (cancelar órdenes de movimiento, deseleccionar, abortar colocación de edificios o activar vender/reparar).
  * **Arrastre con 2 dedos**: Desplazamiento suave de la cámara por el mapa en cualquier dirección.
  * **HUD Táctil Retro Auténtico (Lateral izquierdo de la pantalla)**:
    * **`CTRL` (Ataque Forzado)**: Activa/desactiva el modo de disparo forzado contra el suelo, puentes o unidades aliadas. Incorpora un indicador ámbar iluminado cuando está activo.
    * **`1`, `2`, `3`, `4` (Grupos de Combate)**: Un toque selecciona el grupo asignado (doble toque centra la cámara en él). Mantener pulsado (400ms) asigna las unidades seleccionadas a ese grupo (igual que `Ctrl + 1..4` en PC), confirmado con un LED verde.
    * **`KEY` (Teclado Virtual)**: Muestra u oculta el teclado en pantalla del sistema para escribir nombres de partidas guardadas o códigos.
    * **`▲` / `▼` (Minimizar)**: Pliega el panel táctico a un pequeño botón discreto en la esquina para maximizar el área visible de combate.
* **⚡ Gráficos Acelerados por Hardware**:
  * Backend de vídeo nativo en SDL2 con renderizado acelerado por GPU a resolución nativa.
  * Corrección automática de relación de aspecto 4:3 con escalado nítido y barras negras laterales (*pillarboxing*).
* **🔊 Motor de Sonido y Voces EVA Originales**:
  * Audio a 22.05 kHz con todos los efectos originales, anuncios de voz de EVA en partida y cinemáticas en vídeo (VQA) con audio sincronizado.
* **⚔️ Campañas y Escaramuza 100% Funcionales**:
  * Campañas Aliada y Soviética completas y jugables de principio a fin.
  * Modo Escaramuza local (*Skirmish*) con configuración de número de oponentes y dificultad.
* **💾 Almacenamiento Seguro de Partidas Guardadas**:
  * Guardado automático en el sandbox de la app en iPadOS/iOS (`Documents/`), persistiendo entre reinicios y actualizaciones.

---

## 🏛️ Arquitectura del Sistema

```
┌────────────────────────────────────────────────────────┐
│             Capa Anfitrión (Host)                      │
│   • iPadOS: UIKit, UIScene, orientación landscape fija │
└──────────────────────────┬─────────────────────────────┘
                           │
                           ▼
┌────────────────────────────────────────────────────────┐
│             Capa de Plataforma y Entrada SDL2          │
│   • Renderizado de superficie acelerado por GPU        │
│   • Despacho de eventos táctiles multitoque y gestos   │
│   • Mezcla de audio (DirectSound / WinMM shims)        │
└──────────────────────────┬─────────────────────────────┘
                           │
                           ▼
┌────────────────────────────────────────────────────────┐
│      Motor de Gestos y HUD Táctil Retro (1996)         │
│   • Renderizador de chapa metálica industrial Westwood │
│   • Detección táctil, ataque forzado y grupos 1..4     │
│   • Máquina de estados para selección múltiple en caja │
└──────────────────────────┬─────────────────────────────┘
                           │
                           ▼
┌────────────────────────────────────────────────────────┐
│         Motor Principal Westwood Red Alert 95          │
│   • CONQUER, DISPLAY, SCENARIO, SIDEBAR, TAB, MAP, AI  │
│   • Sistema de archivos virtual de paquetes .MIX y LCW │
│   • Decodificador de vídeo VQA y reproductor de sonido │
└────────────────────────────────────────────────────────┘
```

---

## ⚠️ Aviso Crítico sobre los Datos del Juego

> **ESTE REPOSITORIO NO CONTIENE ARCHIVOS CON DERECHOS DE AUTOR DEL JUEGO ORIGINAL**
> 
> En estricto cumplimiento de las leyes de propiedad intelectual y los términos de Electronic Arts, este repositorio contiene **únicamente código fuente y herramientas de compilación**. No se distribuyen paquetes `.MIX`, archivos de audio, música, vídeos ni imágenes de disco.
> 
> Para jugar, debes aportar tus propios archivos obtenidos de los discos originales de Red Alert.

### Cómo Obtener los Archivos Legalmente

En 2008, Electronic Arts liberó oficialmente Command & Conquer: Red Alert como software **gratuito (freeware)** para celebrar su 12º aniversario. Puedes utilizar:
1. Las imágenes ISO oficiales freeware de EA:
   * **Disco Aliado**: `CD1_ALLIED_DISC.ISO`
   * **Disco Soviético**: `CD2_SOVIET_DISC.ISO`
2. O tus propios discos compactos originales de 1996 o copias de seguridad personales.

---

## 🚀 Tutorial Paso a Paso: De Cero a Jugar en iPad

Sigue estos sencillos pasos para compilar e instalar el juego:

### Paso 1: Clonar este Repositorio

Abre la aplicación **Terminal** en tu Mac y clona el proyecto:

```bash
git clone https://github.com/MargeLenders/redalert-ipad.git
cd redalert-ipad
```

*(O clona tu propio fork si lo has bifurcado en GitHub).*

---

### Paso 2: Instalar Dependencias de Compilación

En macOS, instala CMake, Ninja y SDL2 mediante [Homebrew](https://brew.sh/):

```bash
brew install cmake ninja pkg-config sdl2
xcode-select --install
```

Asegúrate de tener instalado **Xcode completo** desde el Mac App Store (no solo las Command Line Tools) si deseas compilar para iPad/iOS.

---

### Paso 3: Preparar los Datos del Juego (Discos / ISOs)

1. **Monta las dos imágenes de disco** haciendo doble clic sobre ellas en Finder o desde la terminal:
   ```bash
   hdiutil mount /ruta/a/CD1_ALLIED_DISC.ISO
   hdiutil mount /ruta/a/CD2_SOVIET_DISC.ISO
   ```
   *(Aparecerán montadas en `/Volumes/CD1` o `/Volumes/REDALERT` y `/Volumes/CD2`).*

2. **Ejecuta el script de preparación automática**:
   ```bash
   scripts/prepare_assets_from_local.sh \
     --allies /Volumes/CD1 \
     --soviet /Volumes/CD2
   ```

3. **Desmonta las imágenes**:
   ```bash
   hdiutil unmount /Volumes/CD1
   hdiutil unmount /Volumes/CD2
   ```

*El script copiará los archivos esenciales `.MIX` y `INSTALL/REDALERT.INI` a la carpeta local `assets/redalert/` (ignorada en git).*

---

### Paso 6: Instalar en tu iPad

Puedes compilar e instalar el juego usando una **cuenta gratuita de Apple ID** (no es necesaria la suscripción anual de \$99/año).

1. **Obtén tu Apple Development Team ID**:
   * En Xcode: Abre **Settings** (`Cmd + ,`) $\rightarrow$ pestaña **Accounts** $\rightarrow$ selecciona tu Apple ID $\rightarrow$ **Manage Certificates** (tu Team ID de 10 caracteres alfanuméricos aparece junto a tu nombre).
   * O consúltalo en [developer.apple.com/account](https://developer.apple.com/account).

2. **Compila la versión optimizada Release para dispositivo**:
   ```bash
   RA_IOS_DEVELOPMENT_TEAM=TU_TEAM_ID scripts/build_ios_debug.sh --device --release
   ```
   *(Sustituye `TU_TEAM_ID` por tu Team ID).*

3. **Instalar en el iPad con Xcode**:
   * Conecta tu iPad al Mac mediante cable USB y pulsa **Confiar en este ordenador** en la pantalla del iPad.
   * Abre el proyecto generado en Xcode:
     ```bash
     open ios/build-device/redalert_ios.xcodeproj
     ```
   * En la barra superior de Xcode, selecciona tu iPad como dispositivo de destino.
   * Pulsa el botón **Play / Run** (`Cmd + R`). Xcode firmará la app, incluirá los datos locales preparados y la instalará en tu iPad.

4. **Activar el Modo Desarrollador y Confiar en el Certificado en el iPad**:
   * En iPadOS 16/17+: Ve a **Ajustes $\rightarrow$ Privacidad y seguridad $\rightarrow$ Modo Desarrollador**, actívalo y reinicia el iPad.
   * Tras reiniciar, ve a **Ajustes $\rightarrow$ General $\rightarrow$ Gestión de dispositivos y VPN**, pulsa en tu Apple ID bajo *App de desarrollador* y selecciona **Confiar**.
   * ¡Abre **Red Alert** desde la pantalla de inicio de tu iPad y a jugar!

---

## 🎮 Referencia de Controles Táctiles en iPad

| Gesto / Entrada | Acción en el Juego | Descripción |
| :--- | :--- | :--- |
| **Toque con 1 dedo** | **Acción Principal / Clic Izquierdo** | Seleccionar unidad, mover, atacar, colocar construcciones, interactuar con la barra lateral. |
| **Arrastre con 1 dedo** | **Selección Múltiple en Caja** | Dibuja una caja de selección verde para seleccionar múltiples unidades de combate a la vez. |
| **Toque con 2 dedos** | **Clic Derecho / Cancelar** | Cancelar órdenes, deseleccionar unidades, abortar colocación de estructuras o modo vender/reparar. |
| **Arrastre con 2 dedos** | **Desplazamiento del Mapa** | Mueve suavemente la cámara por el terreno en cualquier dirección. |
| **HUD: `CTRL`** | **Ataque Forzado** | Fuerza el disparo contra el suelo, puentes o estructuras (indicador ámbar activo). |
| **HUD: `1`..`4` (Toque)** | **Seleccionar Grupo de Combate** | Selecciona el grupo asignado. Doble toque rápido salta la cámara a su posición. |
| **HUD: `1`..`4` (Mantener)**| **Asignar Grupo de Combate** | Pulsación larga (400ms) asigna las unidades seleccionadas al grupo (confirmado por LED verde). |
| **HUD: `KEY`** | **Teclado Virtual** | Muestra el teclado en pantalla del sistema para escribir nombres o códigos. |
| **HUD: `▲` / `▼`** | **Minimizar HUD** | Pliega el dock a un botón de esquina para despejar el campo de visión. |
| **Ratón / Trackpad** | **Puntero de Escritorio** | Compatible de forma transparente con ratones, Magic Keyboards y trackpads Bluetooth. |

---

## 📂 Estructura del Repositorio

```
.
├── CMakeLists.txt              # Configuración raíz de compilación CMake
├── CODE/                       # Motor de juego original de Westwood en C++
├── PORT/
│   ├── MAC/                    # Runtime compartido y capa SDL2
│   │   ├── include/
│   │   │   ├── mobile_touch_hud.h      # Estado y controles del HUD táctil
│   │   │   ├── mobile_touch_art.h      # Gráficos retro industriales Westwood (1996)
│   │   │   └── mobile_touch_gesture.h  # Gestor de gestos multitoque
│   │   └── src/
│   │       └── mac_sdl_runtime.cpp     # Ventana, audio y canal de renderizado SDL2
│   ├── IOS/                    # Punto de entrada y sandbox para iOS
│   └── ANDROID/                # Punto de entrada para Android
├── ios/                        # Target CMake y catálogo de assets para iOS
│   ├── Assets.xcassets         # Icono soviético retro de la aplicación
│   ├── CMakeLists.txt          # Generador del proyecto Xcode
│   └── Info.plist.in           # Plantilla del archivo de propiedades iOS
├── android/                    # Proyecto Gradle para Android
├── scripts/                    # Scripts auxiliares de compilación y ejecución
│   ├── prepare_assets_from_local.sh  # Empaquetador de archivos originales del juego
│   ├── build_ios_debug.sh      # Compilador automatizado para simulador y dispositivo
│   ├── run_ios_simulator.sh    # Lanza el simulador en horizontal con la app
│   └── run_mac_dev.sh          # Lanzador de escritorio para macOS
├── tests/                      # Pruebas unitarias (incluyendo tests del HUD y gestos)
├── README.md                   # Documentación en inglés
└── README.es.md                # Esta documentación en español
```

---

## ❓ Preguntas Frecuentes y Solución de Problemas

#### P: La compilación falla con *"Missing local Red Alert assets under assets/redalert"*.
**R:** No se han preparado los datos del juego. Sigue el Paso 3 del tutorial: monta las dos imágenes de disco (Allies y Soviet) y ejecuta `scripts/prepare_assets_from_local.sh`.

#### P: ¿Cuánto tiempo dura la app en el iPad con un Apple ID gratuito?
**R:** Apple permite ejecutar apps instaladas mediante cuenta personal gratuita durante **7 días**. Transcurrido ese tiempo, simplemente vuelve a conectar el iPad al Mac, abre el proyecto en Xcode y pulsa **Run** (`Cmd + R`) para renovarla otros 7 días sin perder tus partidas guardadas. (Con cuenta de pago dura 365 días).

#### P: Xcode muestra el error *"Failed to register bundle identifier"*.
**R:** Los Bundle Identifiers deben ser únicos en los servidores de Apple. Especifica uno propio al compilar:
```bash
RA_IOS_BUNDLE_IDENTIFIER="com.tu_nombre.redalert" scripts/build_ios_debug.sh --device --release
```

#### P: ¿Dónde se guardan las partidas en el iPad?
**R:** Se almacenan en el sandbox aislado de la app (`Documents/`), persistiendo entre sesiones de juego y reinstalaciones de la app.

---

## ⚖️ Declaración Legal y Licencias

* **Command & Conquer: Red Alert**: © 1996 Electronic Arts Inc. Todos los derechos reservados. Ni este repositorio ni sus autores distribuyen material con derechos de autor, ejecutables propietarios ni archivos de audio/vídeo del juego original.
* **Port upstream**: Basado en el trabajo de código abierto de [`dk8827/ra-port`](https://github.com/dk8827/ra-port) y en la liberación bajo GPLv3 de Electronic Arts (<https://github.com/electronicarts/CnC_Red_Alert>).
* **Licencia**: Publicado bajo la licencia de código abierto **GNU General Public License v3 (GPLv3)** con términos adicionales. Consulta [LICENSE.md](LICENSE.md) y [NOTICE.md](NOTICE.md).
