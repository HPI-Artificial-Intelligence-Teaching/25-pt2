# Demonstrates the birthday paradox

# 2025 by Ralf Herbrich
# Hasso Plattner Institut

using Plots

M = 365
N = 80


function q(n, M)
    if (n == M + 1)
        return 1
    else
        return (n + 1) / M * q(n + 1, M)
    end
end

# plot the key distribution on the screen
p = plot(1:N, map(n -> 1 - q(M - n, M), 1:N), legend = false, linewidth = 3)
scatter!(1:N, map(n -> 1 - q(M - n, M), 1:N))
ylabel!("P(Collision|M=365)")
xlabel!("n")
display(p)
