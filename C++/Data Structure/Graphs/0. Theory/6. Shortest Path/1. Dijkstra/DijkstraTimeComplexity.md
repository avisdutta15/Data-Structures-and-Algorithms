# Dijkstra's Algorithm

## Pseudocode

```
DIJKSTRA(G, source):
    INITIALIZE-SINGLE-SOURCE(G, source)
    // Set dist[source] = 0, dist[v] = ∞ for all other v
    // Set parent[v] = NULL for all v

    PQ = priority queue containing all vertices with their dist[] values

    while (!PQ.empty()):
        (u, costToU) = PQ.pop()          // extract vertex with minimum distance
        for each neighbour v of u:
            Relax(u, v, weight)
```

---

## Variation 1: Decrease-Key Based (Textbook Approach)

### Relax with Decrease-Key

```
RELAX(u, v, weight):
    if dist[u] + weight(u, v) < dist[v]:
        dist[v] = dist[u] + weight(u, v)
        parent[v] = u
        PQ.decrease-key(v, dist[v])      // update v's priority IN-PLACE
```

In this version, the priority queue always holds exactly one entry per vertex. When we find a shorter path to v, we locate v inside the heap and update its key directly.

### Time Complexity Analysis (Decrease-Key Version)

**Heap size:** Always ≤ V (one entry per vertex)

**Step 1: Initialization**
- Setting up dist[], parent[], and inserting all V vertices into PQ → O(V)

**Step 2: The outer while loop runs exactly V times**
- Every vertex enters the PQ once and gets popped exactly once.
- Each `PQ.pop()` (extract-min) costs O(log V) because heap size ≤ V.
- Total cost of all extract-min operations: **O(V · log V)**

**Step 3: The inner for-loop across all iterations processes every edge**
- Over the entire algorithm, each edge is examined once (directed) or twice (undirected).
- Total relaxation calls = O(E). Here's why:

  Each vertex u gets popped exactly once. When u is popped, we iterate over all edges leaving u.
  By the time the algorithm finishes, we've looked at the edges from every vertex exactly once.
  That means we've examined every edge in the graph exactly once (directed) or twice (undirected).
  It's not E per iteration — it's E total, summed over all iterations.

  Example (4 vertices, 5 edges):
  ```
  Pop A → edges: A→B, A→C        (2 relax calls)
  Pop B → edges: B→C, B→D        (2 relax calls)
  Pop C → edges: C→D             (1 relax call)
  Pop D → edges: (none)          (0 relax calls)
                                   ─────────────────
                                   Total: 5 = E
  ```

- Each relaxation may call `decrease-key`, which costs O(log V) (bubble-up in a heap of size ≤ V).
- Total cost of all decrease-key operations: **O(E · log V)**

**Total:**

```
O(V)  +  O(V · log V)  +  O(E · log V)
=  O((V + E) · log V)
```

For connected graphs (E ≥ V - 1), this simplifies to **O(E · log V)**.

---

## Variation 2: Lazy Deletion (No Decrease-Key)

### Relax with Lazy Insertion

```
RELAX(u, v, weight):
    if dist[u] + weight(u, v) < dist[v]:
        dist[v] = dist[u] + weight(u, v)
        parent[v] = u
        PQ.push(v, dist[v])             // push NEW entry, don't remove old one
```

The main loop also changes slightly to skip stale entries:

```
while (!PQ.empty()):
    (u, costToU) = PQ.pop()
    if costToU > dist[u]:
        continue                         // stale entry, skip it
    for each neighbour v of u:
        Relax(u, v, weight)
```

In this version, we never search for v inside the heap. Instead, we just push a brand new entry every time we find a shorter path. The old (stale) entries remain in the heap and are discarded when popped.

### Why the Heap Can Grow to Size E

Each call to `Relax` that finds a shorter path pushes a new entry into PQ without removing the old one. Total relaxation calls across the entire algorithm = O(E) (one per edge). So the heap can accumulate up to E entries at its peak.

**Example:** Vertex C gets relaxed through 3 different edges:

```
PQ state at some point:
(C, 10)   ← from edge B→C (stale)
(C, 7)    ← from edge D→C (stale)
(C, 5)    ← from edge A→C (current best)
```

C appears 3 times. When we pop (C, 5), we process it. When we later pop (C, 7) and (C, 10), we see `costToU > dist[C]` and skip them.

### Time Complexity Analysis (Lazy Deletion Version)

**Heap size:** Can grow up to E

**Step 1: Initialization** → O(V)

**Step 2: PQ.pop() is called at most E times**
- We push at most E entries total (one per relaxation), plus the initial V entries.
- So we pop at most O(V + E) = O(E) times (for connected graphs).
- Each pop costs O(log E) because heap size ≤ E.
- Total cost of all pops: **O(E · log E)**

**Step 3: PQ.push() is called at most E times**
- Each push costs O(log E).
- Total cost of all pushes: **O(E · log E)**

**Total:**

```
O(E · log E) + O(E · log E) = O(E · log E)
```

### Why O(log E) = O(log V) — They're Asymptotically the Same

For any simple graph (no self-loops, no duplicate edges):

```
E ≤ V × (V-1) / 2 ≤ V²
```

This is because the maximum number of edges occurs when every vertex connects to every other vertex.

Therefore:

```
log E  ≤  log(V²)  =  2 · log V
```

(Using the logarithm property: log(a^b) = b · log a)

Since O(2 · log V) = O(log V) (constants vanish in Big-O):

**O(log E) = O(log V)**

Concrete example: V = 1000, E ≤ 1,000,000
- log₂(1000) ≈ 10
- log₂(1,000,000) ≈ 20

log E is at most 2× log V — just a constant factor.

### Final Result for Lazy Deletion

```
O(E · log E) = O(E · log V)
```

Same asymptotic complexity as the decrease-key version.

---

## Summary

| Version | Heap Size | Key Operations | Total Complexity |
|---------|-----------|----------------|-----------------|
| Decrease-Key | ≤ V | V pops + E decrease-keys, each O(log V) | O((V + E) · log V) |
| Lazy Deletion | ≤ E | E pops + E pushes, each O(log E) = O(log V) | O(E · log V) |

Both give **O(E · log V)** for connected graphs with a binary heap.
