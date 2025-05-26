#! julia
# Demonstrates properties of modulo hashing
#
# 2025 by Ralf Herbrich
# Hasso Plattner Institut

using Plots

"""
    read_ips(file_name)

Reads the IP addresses from the input file
"""
function read_ips(file_name)
    ips = Vector{Tuple{String,String,String,String}}()

    # read the IP addresses from the file
    open(file_name, "r") do file
        # skip the header line
        readline(file)

        while (!eof(file))
            m = match(
                r"(\d+).(\d+).(\d+).(\d+)\/(\d+),(\d+),(.+),(.+),(.+),(.+),(.+),(.+)",
                readline(file),
            )
            if (!isnothing(m))
                d = (String(m[1]), String(m[2]), String(m[3]), String(m[4]))
                push!(ips, d)
            end
        end
    end

    return (ips)
end

"""
    demo_hash(filename)

Demonstrates a modular has on a file full of IP4 addresses
"""
function demo_hash(file_name)
    # converts a string of IPs to a unique IP integer
    function ip_str_to_int64((ip1, ip2, ip3, ip4), base = 256)::Int64
        key = parse(Int64, ip1)
        key = key * base + parse(Int64, ip2)
        key = key * base + parse(Int64, ip3)
        key = key * base + parse(Int64, ip4)
        return (key)
    end

    # generates a key distribution plot for a given hash function
    function key_distribution_plot(ips, hash_fct, M)
        # convert to integers and compute the key
        counts = zeros(M)
        for key in map(ip_str_to_int64, ips)
            counts[hash_fct(key, M)+1] += 1
        end

        # plot the key distribution on the screen
        p = bar(1:length(counts), counts, legend = false)
        plot!([1, M], [sum(counts) / M, sum(counts) / M], linewidth = 3)
        ylabel!("Count")
        xlabel!("Hash Key")
        return p
    end

    # computes the hash-key
    function mod_hash(key::Int64, M)::Int64
        return (mod(key, M))
    end

    # computes the multiplicative hash-key
    function mult_hash(key::Int64, M)::Int64
        a = (sqrt(5) - 1) / 2
        return (Int64(floor(M * (key * a - floor(key * a)))))
    end

    # computes the multiplicative hash-key when M is a power of two
    function mult_shift_hash(key::Int64, M)::Int64
        a = 2654435769
        l = Int(log(M) / log(2))
        return ((mod(key * a, 2^32)) >> (32 - l))
    end

    # read the IP addresses
    ips = read_ips(file_name)

    plts = [
        # mod_hash
        key_distribution_plot(ips, mod_hash, 96),
        key_distribution_plot(ips, mod_hash, 97),
        key_distribution_plot(ips, mod_hash, 98),
        # mult_hash
        key_distribution_plot(ips, mult_hash, 96),
        key_distribution_plot(ips, mult_hash, 97),
        key_distribution_plot(ips, mult_hash, 98),
        # mult_hash
        key_distribution_plot(ips, mult_hash, 4),
        key_distribution_plot(ips, mult_hash, 8),
        key_distribution_plot(ips, mult_hash, 16),
    ]

    for p in plts
        println("Enter for next. q to close.")
        display(p)
        var = readline()
        if var == "q"
            exit()
        end
    end
end

# main entry of the program
file_name = joinpath(@__DIR__, "geoip2-ipv4.csv")
if (length(ARGS) == 1)
    file_name = ARGS[1]
end

demo_hash(file_name)
