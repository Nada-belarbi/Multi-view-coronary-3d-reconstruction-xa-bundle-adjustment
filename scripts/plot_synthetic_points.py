import pandas as pd
import matplotlib.pyplot as plt
from pathlib import Path


# ============================================================
# CHEMINS
# ============================================================

BASE_DIR = Path(__file__).resolve().parent.parent

CSV_PATH = BASE_DIR / "results" / "synthetic_points.csv"

OUTPUT_DIR = BASE_DIR / "results" / "figures"

OUTPUT_DIR.mkdir(parents=True, exist_ok=True)


# ============================================================
# CHARGEMENT DES DONNEES
# ============================================================

df = pd.read_csv(CSV_PATH)


# ============================================================
# EXTRACTION DES BRANCHES
# ============================================================

main = df[df["branch"].isin(["main", "bifurcation"])]

left = pd.concat([
    df[df["branch"] == "bifurcation"],
    df[df["branch"] == "left"]
])

right = pd.concat([
    df[df["branch"] == "bifurcation"],
    df[df["branch"] == "right"]
])


# ============================================================
# FONCTION POUR AJOUTER LES LABELS
# ============================================================

def ajouter_labels_3d(ax, data):
    for _, point in data.iterrows():
        ax.text(
            point["x"],
            point["y"],
            point["z"],
            point["id"]
        )


def ajouter_labels_2d(ax, data, x_col, y_col):
    for _, point in data.iterrows():
        ax.annotate(
            point["id"],
            (point[x_col], point[y_col]),
            xytext=(5, 5),
            textcoords="offset points"
        )


# ============================================================
# FIGURE 1 : VUE 3D
# ============================================================

fig = plt.figure(figsize=(10, 8))

ax = fig.add_subplot(
    111,
    projection="3d"
)


ax.plot(
    main["x"],
    main["y"],
    main["z"],
    marker="o",
    label="Branche principale"
)

ax.plot(
    left["x"],
    left["y"],
    left["z"],
    marker="o",
    label="Branche gauche"
)

ax.plot(
    right["x"],
    right["y"],
    right["z"],
    marker="o",
    label="Branche droite"
)


ajouter_labels_3d(ax, df)


ax.set_xlabel("X (mm)")
ax.set_ylabel("Y (mm)")
ax.set_zlabel("Z (mm)")

ax.set_title(
    "Bifurcation synthetique - Vue 3D"
)

ax.legend()

ax.grid(True)


# ------------------------------------------------------------
# IMPORTANT :
# On impose une échelle comparable sur X, Y et Z.
# Sinon la géométrie peut sembler déformée visuellement.
# ------------------------------------------------------------

x_min, x_max = df["x"].min(), df["x"].max()
y_min, y_max = df["y"].min(), df["y"].max()
z_min, z_max = df["z"].min(), df["z"].max()

x_range = x_max - x_min
y_range = y_max - y_min
z_range = z_max - z_min

max_range = max(
    x_range,
    y_range,
    z_range
)

x_mid = (x_max + x_min) / 2.0
y_mid = (y_max + y_min) / 2.0
z_mid = (z_max + z_min) / 2.0


ax.set_xlim(
    x_mid - max_range / 2,
    x_mid + max_range / 2
)

ax.set_ylim(
    y_mid - max_range / 2,
    y_mid + max_range / 2
)

ax.set_zlim(
    z_mid - max_range / 2,
    z_mid + max_range / 2
)


plt.tight_layout()

plt.savefig(
    OUTPUT_DIR / "synthetic_points_3D.png",
    dpi=300
)

plt.show()


# ============================================================
# FIGURE 2 : PROJECTION XY
# ============================================================

fig, ax = plt.subplots(figsize=(9, 7))


ax.plot(
    main["x"],
    main["y"],
    marker="o",
    label="Branche principale"
)

ax.plot(
    left["x"],
    left["y"],
    marker="o",
    label="Branche gauche"
)

ax.plot(
    right["x"],
    right["y"],
    marker="o",
    label="Branche droite"
)


ajouter_labels_2d(
    ax,
    df,
    "x",
    "y"
)


ax.set_xlabel("X (mm)")
ax.set_ylabel("Y (mm)")

ax.set_title(
    "Projection XY - Vue de dessus"
)

ax.axis("equal")

ax.grid(True)

ax.legend()

plt.tight_layout()

plt.savefig(
    OUTPUT_DIR / "synthetic_points_XY.png",
    dpi=300
)

plt.show()


# ============================================================
# FIGURE 3 : PROJECTION XZ
# ============================================================

fig, ax = plt.subplots(figsize=(9, 7))


ax.plot(
    main["x"],
    main["z"],
    marker="o",
    label="Branche principale"
)

ax.plot(
    left["x"],
    left["z"],
    marker="o",
    label="Branche gauche"
)

ax.plot(
    right["x"],
    right["z"],
    marker="o",
    label="Branche droite"
)


ajouter_labels_2d(
    ax,
    df,
    "x",
    "z"
)


ax.set_xlabel("X (mm)")
ax.set_ylabel("Z (mm)")

ax.set_title(
    "Projection XZ - Vue de face"
)

ax.axis("equal")

ax.grid(True)

ax.legend()

plt.tight_layout()

plt.savefig(
    OUTPUT_DIR / "synthetic_points_XZ.png",
    dpi=300
)

plt.show()


# ============================================================
# FIGURE 4 : PROJECTION YZ
# ============================================================

fig, ax = plt.subplots(figsize=(9, 7))


ax.plot(
    main["y"],
    main["z"],
    marker="o",
    label="Branche principale"
)

ax.plot(
    left["y"],
    left["z"],
    marker="o",
    label="Branche gauche"
)

ax.plot(
    right["y"],
    right["z"],
    marker="o",
    label="Branche droite"
)


ajouter_labels_2d(
    ax,
    df,
    "y",
    "z"
)


ax.set_xlabel("Y (mm)")
ax.set_ylabel("Z (mm)")

ax.set_title(
    "Projection YZ - Vue de cote"
)

ax.axis("equal")

ax.grid(True)

ax.legend()

plt.tight_layout()

plt.savefig(
    OUTPUT_DIR / "synthetic_points_YZ.png",
    dpi=300
)

plt.show()