# Calibrage multi-vue en imagerie XA par bundle adjustment

Projet C++17 pour la modelisation geometrique d'acquisitions angiographiques
XA et la preparation d'un calibrage multi-vue par bundle adjustment.

## Etat actuel

Les modules implementes permettent de :

- charger les metadonnees JSON, les images et les annotations CSV ;
- construire une camera a partir des metadonnees et d'un isocentre ;
- effectuer des transformations geometriques et projeter des points 3D ;
- generer une bifurcation 3D synthetique et exporter ses points en CSV.

Les dossiers de reconstruction, synchronisation, optimisation, evaluation et
experiences sont encore des squelettes. Le bundle adjustment n'est pas encore
implemente.

L'executable actuel lance uniquement la demonstration des points synthetiques.
Il n'utilise pas les donnees d'acquisition.

## Prerequis

- Un compilateur compatible C++17.
- CMake 3.16 ou plus recent et un outil de compilation (Make ou Ninja).
- OpenCV, Eigen et nlohmann/json.

Les dependances Python sont declarees dans [requirements.txt](./requirements.txt).
Les prerequis C++ y sont egalement rappeles en commentaires et doivent etre
installes separement.

### macOS avec Homebrew

```sh
brew install cmake opencv eigen nlohmann-json
```

### Debian / Ubuntu

```sh
sudo apt update
sudo apt install build-essential cmake libopencv-dev libeigen3-dev nlohmann-json3-dev
```

## Compilation et execution

Dans VS Code avec l'extension CMake Tools :

1. Ouvrir le dossier du projet et selectionner un compilateur C++17.
2. Executer **CMake: Configure**, puis **CMake: Build**.
3. Creer le dossier de sortie et lancer l'executable depuis le dossier de
   compilation `build` :

   ```sh
   mkdir -p results
   cd build
   ./angiography
   ```

Ces commandes supposent que le terminal se trouve initialement a la racine
du projet et que CMake Tools utilise `build` comme dossier de compilation.
Avec un autre dossier de compilation, adapter le chemin de l'executable et le
dossier de travail.

Le programme affiche les points puis ecrit
[`results/synthetic_points.csv`](./results/synthetic_points.csv), avec les colonnes :

```text
id,x,y,z,branch
```

**Important :** le chemin de sortie du programme est actuellement relatif
(`../results/synthetic_points.csv`). Le dossier `results` doit exister et le
programme doit etre lance depuis `build` pour obtenir le chemin indique.

## Visualisation des points synthetiques

Depuis la racine du projet, creer et activer un environnement Python local :

```sh
python3 -m venv .venv
source .venv/bin/activate
python -m pip install -r requirements.txt
python scripts/plot_synthetic_points.py
```

Le script utilise pandas et matplotlib. Il lit `results/synthetic_points.csv`,
qui doit avoir ete genere par l'executable C++, et sauvegarde les figures
dans `results/figures/`. Il affiche egalement les graphiques dans des fenetres.
Lors des prochaines executions, reactiver l'environnement avec
`source .venv/bin/activate` avant de lancer le script.

## Organisation

```text
.
|-- CMakeLists.txt
|-- main.cpp
|-- requirements.txt
|-- src/
|   |-- data/              # Metadonnees, images et annotations
|   |-- geometry/          # Camera, projections et transformations
|   |-- simulation/        # Points synthetiques ; autres fichiers en preparation
|   |-- reconstruction/    # Squelette
|   |-- synchronization/   # Squelette
|   |-- optimization/      # Squelette
|   |-- evaluation/        # Squelette
|   `-- experiments/       # Squelette
|-- source/                # Donnees locales, non versionnees
|   |-- Frames/             
|   |-- annotations/         
|   |-- synchronized/      
|-- results/               # Resultats generes, a versionner sur GitHub
`-- build/                 # Compilation, non versionnee
```

## Donnees d'acquisition

Les donnees sont conservees localement sous `source/`, notamment dans
`Frames/MI_1`, ..., `Frames/MI_5`, `annotations/` et `synchronized/`.
Elles ne sont pas fournies par le code et sont exclues de Git pour eviter de
versionner les acquisitions et les fichiers volumineux.

Le chargeur accepte les metadonnees numeriques JSON sous forme de nombres ou
de chaines numeriques. Les annotations CSV utilisent le format :

```text
cameraId,pointId,frameNumber,timeId,u,v
```

## Resolution des problemes

- **`Eigen/Dense` introuvable :** verifier l'installation d'Eigen et relancer
  la configuration CMake. La cible utilise `Eigen3::Eigen`, qui fournit les
  chemins d'inclusion.
- **OpenCV ou nlohmann/json introuvable :** installer les prerequis puis
  relancer la configuration. Si les bibliotheques sont installees dans un
  emplacement personnalise, renseigner `CMAKE_PREFIX_PATH` dans la
  configuration CMake.
- **Symboles non definis a l'edition de liens :** lors de l'ajout d'un module,
  declarer ses fichiers `.cpp` dans la cible appropriee de
  [CMakeLists.txt](./CMakeLists.txt).
- **Impossible d'ouvrir le CSV de sortie :** verifier le dossier `results`
  et le dossier de travail, comme indique dans la section d'execution.

La configuration IntelliSense de [`.vscode/`](./.vscode/) vise actuellement
macOS ARM64 avec Homebrew ; elle peut necessiter une adaptation sur une autre
machine. La configuration de compilation reste definie par CMake.
