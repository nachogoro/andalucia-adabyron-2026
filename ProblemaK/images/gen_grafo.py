"""Genera la imagen del grafo de flujo para el primer caso del ejemplo."""
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from matplotlib.patches import FancyArrowPatch

fig, ax = plt.subplots(figsize=(11, 7))
ax.set_xlim(0, 11)
ax.set_ylim(0, 7.5)
ax.set_aspect('equal')
ax.axis('off')

# Coordenadas de los nodos
S = (0.8, 3.75)
T = (10.2, 3.75)
players = {
    'P1': (3.2, 6.0),
    'P2': (3.2, 4.5),
    'P3': (3.2, 3.0),
    'P4': (3.2, 1.5),
}
roles = {
    'MAGE':    (7.2, 5.5),
    'PALADIN': (7.2, 3.75),
    'ROGUE':   (7.2, 2.0),
}

# Colores
col_src = '#f4b183'   # naranja
col_ply = '#9dc3e6'   # azul claro
col_rol = '#a9d18e'   # verde claro
col_snk = '#f4b183'

def draw_node(xy, label, color, radius=0.42):
    c = plt.Circle(xy, radius, facecolor=color, edgecolor='black', linewidth=1.3, zorder=3)
    ax.add_patch(c)
    ax.text(xy[0], xy[1], label, ha='center', va='center',
            fontsize=10, fontweight='bold', zorder=4)

def draw_edge(p, q, label=None, color='black', rad=0.0, offset=(0, 0), fontsize=9, lw=1.0):
    arrow = FancyArrowPatch(p, q,
                            arrowstyle='-|>', mutation_scale=12,
                            color=color, linewidth=lw,
                            connectionstyle=f'arc3,rad={rad}', zorder=2,
                            shrinkA=16, shrinkB=16)
    ax.add_patch(arrow)
    if label is not None:
        mx = (p[0] + q[0]) / 2 + offset[0]
        my = (p[1] + q[1]) / 2 + offset[1]
        ax.text(mx, my, label, ha='center', va='center',
                fontsize=fontsize, color=color,
                bbox=dict(boxstyle='round,pad=0.15', facecolor='white',
                          edgecolor='none', alpha=0.85), zorder=5)

# Fuente y sumidero
draw_node(S, 's', col_src, radius=0.38)
draw_node(T, 't', col_snk, radius=0.38)

# Jugadores
for name, xy in players.items():
    draw_node(xy, name, col_ply)

# Roles
for name, xy in roles.items():
    draw_node(xy, name, col_rol, radius=0.55)

# Aristas fuente -> jugadores (capacidad 1)
for p in players.values():
    draw_edge(S, p, '1', color='#555555', offset=(0, 0.12))

# Aristas jugadores -> roles
edges_pr = [
    ('P1', 'MAGE'), ('P1', 'PALADIN'),
    ('P2', 'PALADIN'), ('P2', 'ROGUE'),
    ('P3', 'ROGUE'), ('P3', 'MAGE'),
    ('P4', 'MAGE'), ('P4', 'ROGUE'),
]
for pl, ro in edges_pr:
    draw_edge(players[pl], roles[ro], '1', color='#1f77b4', lw=1.2,
              offset=(0, 0.08), fontsize=8)

# Aristas roles -> sumidero (capacidad floor(N/K) = 4)
for r in roles.values():
    draw_edge(r, T, '4', color='#2e7d32', offset=(0, 0.12), lw=1.5)

# Etiquetas de columnas
ax.text(3.2, 7.1, 'Jugadores', ha='center', fontsize=12, fontweight='bold')
ax.text(7.2, 7.1, 'Roles', ha='center', fontsize=12, fontweight='bold')
ax.text(S[0], S[1] + 0.85, 'Fuente', ha='center', fontsize=11, fontweight='bold')
ax.text(T[0], T[1] + 0.85, 'Sumidero', ha='center', fontsize=11, fontweight='bold')

# Título
ax.text(5.5, 7.35,
        'Red de flujo del primer caso:  N=12, M=4, K=3  →  límite por rol = ⌊12/3⌋ = 4',
        ha='center', fontsize=11, style='italic')

plt.tight_layout()
plt.savefig('/home/idgc/projects/andalucia-adabyron-2026/ProblemaK/images/grafo_bipartito.png',
            dpi=160, bbox_inches='tight')
print('OK')
