import cupy as cp

def initialize_vector(size):
    return cp.random.randint(0, 10, size)

def initialize_matrix(size):
    return cp.random.randint(0, 10, (size, size))

def add_vectors(A, B):
    return A + B

def multiply_matrices(A, B):
    return A @ B

def print_vector(vector):
    print(' '.join(map(str, cp.asnumpy(vector))))

def print_matrix(matrix):
    for row in cp.asnumpy(matrix):
        print(' '.join(map(str, row)))
    print()

def main():
    N = 4

    A = initialize_vector(N)
    B = initialize_vector(N)

    print("Vector A:")
    print_vector(A)
    
    print("Vector B:")
    print_vector(B)

    C = add_vectors(A, B)

    print("Addition:")
    print_vector(C)

    D = initialize_matrix(N)
    E = initialize_matrix(N)

    print("\nMatrix D:")
    print_matrix(D)

    print("Matrix E:")
    print_matrix(E)

    F = multiply_matrices(D, E)

    print("Multiplication:")
    print_matrix(F)

if __name__ == "__main__":
    main()
