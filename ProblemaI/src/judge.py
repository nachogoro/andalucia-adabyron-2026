#!/usr/bin/env python3
"""Juez para el Problema I (Numble).

Ejecuta 700 tests aleatorios deterministas contra una solución externa,
siguiendo el protocolo descrito en el enunciado.

Uso:
    python3 judge.py <comando de la solución>

Ejemplos:
    python3 judge.py ./a.out
    python3 judge.py python3 solucion.py

Escribe en `judge_log.txt` el detalle de los fallos encontrados y, al
terminar, imprime el número medio de consultas usadas por la solución.
"""
import sys
import random
import select
import subprocess
from collections import Counter

NUM_TESTS    = 700
# El enunciado permite hasta Q=20. Aquí usamos 15: da margen cómodo a la
# estrategia "consultar iii..i para i=1..N y luego elegir al azar entre
# candidatos consistentes" (que en estos 700 tests nunca necesita más de
# 11), y descarta estrategias claramente malas que no filtran con la
# retroalimentación.
MAX_QUERIES  = 15
READ_TIMEOUT = 5.0       # segundos


def safe_readline(stdout, timeout=READ_TIMEOUT):
    fd = stdout.fileno()
    ready, _, _ = select.select([fd], [], [], timeout)
    if not ready:
        return None
    return stdout.readline()


def feedback(guess, secret):
    L = len(guess)
    v = sum(1 for i in range(L) if guess[i] == secret[i])
    cs, cg = Counter(), Counter()
    for i in range(L):
        if guess[i] != secret[i]:
            cs[secret[i]] += 1
            cg[guess[i]] += 1
    a = sum(min(cg[d], cs[d]) for d in cg)
    return v, a


def parse_line(line, prefix, L, N):
    """Parsea una línea del tipo `? g1g2..gL` o `! s1s2..sL`.

    Se admiten espacios o tabuladores entre los dígitos. Devuelve la lista
    de enteros o None si el formato no es válido.
    """
    if not line or line[0] != prefix:
        return None
    rest = line[1:].replace(' ', '').replace('\t', '')
    if len(rest) != L:
        return None
    digits = []
    for c in rest:
        if not c.isdigit():
            return None
        d = int(c)
        if not (1 <= d <= N):
            return None
        digits.append(d)
    return digits


def run_test(proc, test_id, log):
    L = random.randint(1, 6)
    N = random.randint(1, 6)
    Q = MAX_QUERIES
    secret = [random.randint(1, N) for _ in range(L)]
    secret_s = ''.join(str(x) for x in secret)

    def kill_and_log(msg):
        log.write(f"Test {test_id}: {msg} "
                  f"(L={L}, N={N}, Q={Q}, secret={secret_s})\n")

    try:
        proc.stdin.write(f"{L} {N} {Q}\n".encode())
        proc.stdin.flush()
    except BrokenPipeError:
        kill_and_log("BROKEN PIPE enviando cabecera")
        return -1

    queries = 0
    while True:
        raw = safe_readline(proc.stdout)
        if raw is None:
            kill_and_log(f"HANG (sin respuesta en {READ_TIMEOUT}s)")
            return -1
        if raw == b'':
            kill_and_log("EOF (la solución cerró stdout)")
            return -1
        line = raw.decode().strip()
        if not line:
            continue

        if line.startswith('?'):
            queries += 1
            if queries > Q:
                kill_and_log(f"TOO MANY QUERIES (>{Q})")
                return -1
            g = parse_line(line, '?', L, N)
            if g is None:
                kill_and_log(f"INVALID QUERY {line!r}")
                return -1
            v, a = feedback(g, secret)
            try:
                proc.stdin.write(f"{v} {a}\n".encode())
                proc.stdin.flush()
            except BrokenPipeError:
                kill_and_log(f"BROKEN PIPE tras la consulta #{queries}")
                return -1

        elif line.startswith('!'):
            g = parse_line(line, '!', L, N)
            if g is None:
                kill_and_log(f"INVALID ANSWER {line!r}")
                return -1
            if g == secret:
                return queries
            got = ''.join(str(x) for x in g)
            kill_and_log(f"WRONG ANSWER got={got} queries={queries}")
            return -1

        # cualquier otra línea se ignora (puede ser debug de la solución)


def main():
    if len(sys.argv) < 2:
        print("Uso: judge.py <comando de la solución>", file=sys.stderr)
        sys.exit(1)

    sol_cmd = sys.argv[1:]
    random.seed(12345)

    try:
        proc = subprocess.Popen(
            sol_cmd,
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.DEVNULL,
            close_fds=True,
        )
    except (FileNotFoundError, PermissionError, OSError) as exc:
        print(f"Error al lanzar {sol_cmd}: {exc}", file=sys.stderr)
        sys.exit(1)

    total_queries = 0
    completed = 0
    failed = False
    try:
        with open("judge_log.txt", "w") as log:
            for tid in range(1, NUM_TESTS + 1):
                result = run_test(proc, tid, log)
                if result < 0:
                    print(f"Test {tid}: FALLÓ (ver judge_log.txt)", file=sys.stderr)
                    failed = True
                    break
                total_queries += result
                completed += 1

            if not failed:
                try:
                    proc.stdin.write(b"0\n")
                    proc.stdin.flush()
                except BrokenPipeError:
                    pass
    finally:
        try: proc.stdin.close()
        except Exception: pass
        try: proc.stdout.close()
        except Exception: pass
        try:
            proc.wait(timeout=2.0)
        except subprocess.TimeoutExpired:
            proc.kill()
            proc.wait()

    print(f"Tests superados: {completed}/{NUM_TESTS}")
    if completed > 0:
        print(f"Consultas medias: {total_queries / completed:.2f}")
    sys.exit(0 if not failed else 1)


if __name__ == '__main__':
    main()
