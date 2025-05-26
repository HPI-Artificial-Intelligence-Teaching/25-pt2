# Demonstrates properties of hashing with linear probing
#
# 2025 by Ralf Herbrich
# Hasso Plattner Institut

using Plots
using Colors

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
    demo_linear_probing_hash(filename)

Demonstrates clustering of hasing with linear probing
"""
function demo_linear_probing_hash(file_name)
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
        # Correct the hash-keys for plotting
        y = Int64(ceil(sqrt(M / 2)))
        x = 2 * y
        M = x * y

        # convert to integers and compute the key
        hash_set = zeros(M)
        # setup the probe counter
        prob_cnt = 0
        key_cnt = 0
        for key in map(ip_str_to_int64, ips)
            hash_key = hash_fct(key, M) + 1
            key_cnt += 1

            prob_cnt += 1
            while (hash_set[hash_key] == 1)
                prob_cnt += 1
                hash_key = mod(hash_key, M) + 1
            end

            hash_set[hash_key] = 1
        end

        # plot the key distribution on the screen
        p = heatmap(reshape(hash_set, y, x), color = (:greys))
        display(p)
        println("Average number of probes: ", prob_cnt / key_cnt)
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

    # read the IP addresses
    ips = read_ips(file_name)
    M = length(ips) * 2        # this ensures that α=1/2

    key_distribution_plot(ips, mod_hash, M)
    key_distribution_plot(ips, mult_hash, M)

end

# main entry of the program
file_name = "/Users/rherbrich/src/overleaf/HPI/Programmiertechnik II/unit7/geoip2-ipv4.csv"
if (length(ARGS) == 1)
    file_name = ARGS[1]
end

demo_linear_probing_hash(file_name)
