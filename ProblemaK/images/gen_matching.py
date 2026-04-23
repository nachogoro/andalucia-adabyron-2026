"""Genera la imagen del grafo bipartito (jugadores vs asientos de rol)
para el primer caso del ejemplo, con un emparejamiento máximo resaltado."""
import matplotlib.pyplot as plt
from matplotlib.patches import FancyBboxPatch

fig, ax = plt.subplots(figsize=(12, 12))
ax.set_xlim(0, 12)
ax.set_ylim(-0.5, 13)
ax.set_aspect('equal')
ax.axis('off')

# --- Jugadores (lado izquierdo) ---
players = {
    'P1': (2.0, 9.0),
    'P2': (2.0, 6.8),
    'P3': (2.0, 4.6),
    'P4': (2.0, 2.4),
}
player_roles = {
    'P1': ('MAGE', 'PALADIN'),
    'P2': ('PALADIN', 'ROGUE'),
    'P3': ('ROGUE', 'MAGE'),
    'P4': ('MAGE', 'ROGUE'),
}

# --- Asientos (lado derecho), agrupados por rol ---
L = 4
roles_order = ['MAGE', 'PALADIN', 'ROGUE']
group_top = {'MAGE': 9.9, 'PALADIN': 6.5, 'ROGUE': 3.1}
slots = {}
for rol in roles_order:
    top = group_top[rol]
    for i in range(L):
        slots[(rol, i)] = (9.0, top - 0.75 * i)

# Colores
col_ply = '#9dc3e6'
col_rol = '#a9d18e'
col_edge_bg = '#b0b0b0'
col_match = '#c0392b'

def draw_node(xy, label, color, radius=0.34, fontsize=10):
    c = plt.Circle(xy, radius, facecolor=color, edgecolor='black',
                   linewidth=1.2, zorder=3)
    ax.add_patch(c)
    ax.text(xy[0], xy[1], label, ha='center', va='center',
            fontsize=fontsize, fontweight='bold', zorder=4)

def draw_edge(p, q, color, lw, alpha=1.0, zorder=2):
    ax.plot([p[0], q[0]], [p[1], q[1]],
            color=color, linewidth=lw, alpha=alpha, zorder=zorder,
            solid_capstyle='round')

# Cajas de fondo por rol + etiqueta a la derecha de la caja
for rol in roles_order:
    top = group_top[rol]
    bottom = top - 0.75 * (L - 1)
    box = FancyBboxPatch(
        (8.50, bottom - 0.45), 1.0, top - bottom + 0.9,
        boxstyle='round,pad=0.02,rounding_size=0.12',
        facecolor='#eef7e7', edgecolor='#6b8e51',
        linewidth=1.1, zorder=1)
    ax.add_patch(box)
    ax.text(9.85, (top + bottom) / 2, rol,
            ha='left', va='center',
            fontsize=12, fontweight='bold', color='#2d4a1e')

# --- Dibujar TODAS las aristas posibles (tenues) ---
for pl, (ra, rb) in player_roles.items():
    for rol in (ra, rb):
        for i in range(L):
            draw_edge(players[pl], slots[(rol, i)],
                      col_edge_bg, lw=0.8, alpha=0.30, zorder=2)

# --- Emparejamiento máximo a resaltar ---
matching = [
    ('P1', ('MAGE', 0)),
    ('P2', ('PALADIN', 0)),
    ('P3', ('ROGUE', 0)),
    ('P4', ('MAGE', 1)),
]
for pl, slot in matching:
    draw_edge(players[pl], slots[slot], col_match, lw=2.6, alpha=1.0, zorder=5)

# --- Nodos (delante de las aristas) ---
for name, xy in players.items():
    draw_node(xy, name, col_ply, radius=0.42, fontsize=11)
for (rol, i), xy in slots.items():
    draw_node(xy, f'{rol[0]}{i+1}', col_rol, radius=0.30, fontsize=8)

# Título
ax.text(6.0, 12.4,
        'Grafo bipartito del primer caso',
        ha='center', va='center', fontsize=14, fontweight='bold')
ax.text(6.0, 11.85,
        r'$M = 4$ jugadores       $K \cdot L = 3 \cdot 4 = 12$ asientos'
        r'       ($L = \lfloor N/K \rfloor = 4$)',
        ha='center', va='center', fontsize=11, style='italic')

# Etiquetas de columnas
ax.text(2.0, 11.0, 'Jugadores', ha='center',
        fontsize=12, fontweight='bold')
ax.text(9.0, 11.0, 'Asientos por rol', ha='center',
        fontsize=12, fontweight='bold')

# Leyenda
ax.plot([0.3, 1.2], [0.2, 0.2], color=col_edge_bg, lw=1.2, alpha=0.7)
ax.text(1.35, 0.2, 'arista posible', va='center', fontsize=10)
ax.plot([4.2, 5.1], [0.2, 0.2], color=col_match, lw=2.6)
ax.text(5.25, 0.2, 'arista del emparejamiento máximo',
        va='center', fontsize=10)

plt.savefig('/home/idgc/projects/andalucia-adabyron-2026/ProblemaK/images/grafo_matching.png',
            dpi=160, bbox_inches='tight')
print('OK')
