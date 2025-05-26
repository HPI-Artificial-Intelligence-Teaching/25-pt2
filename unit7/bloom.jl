# Demonstrates a Bloom filter
#
# 2025 by Ralf Herbrich
# Hasso Plattner Institut

using Plots
using Random

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
    demo_bloom(filename)

Demonstrates a Bloom filter
"""
function demo_bloom(file_name)
    # converts a string of IPs to a unique IP integer
    function ip_str_to_int64((ip1, ip2, ip3, ip4), base = 256)::Int64
        key = parse(Int64, ip1)
        key = key * base + parse(Int64, ip2)
        key = key * base + parse(Int64, ip3)
        key = key * base + parse(Int64, ip4)
        return (key)
    end

    # computes the multiplicative hash-key
    function mult_hash(a, M)
        return (key::Int64) -> Int64(floor(M * (key * a - floor(key * a))))
    end

    # generates a key distribution plot for a given hash function
    function eval_bloom(ips, k, M)
        # initialize the Bloom filter
        hash_set = zeros(M)

        # intialize the random hash functions
        hash_fcts = map(a -> mult_hash(a, M), rand(Float64, (k, 1)))

        # setup the probe counter
        error_cnt = 0
        for key in map(ip_str_to_int64, ips)
            # compute all the hash keys
            hash_keys = map(h -> h(key) + 1, hash_fcts)

            # check if they are all set (should not happen!)
            if (all(hash_key -> hash_set[hash_key] == 1, hash_keys))
                error_cnt += 1
            end

            # and then set all the hash-keys
            for hash_key in hash_keys
                hash_set[hash_key] = 1
            end
        end

        println("False positive rate: ", error_cnt / length(ips))
    end


    # read the IP addresses
    ips = read_ips(file_name)

    eval_bloom(ips, 1, 10 * length(ips))
    eval_bloom(ips, 2, 10 * length(ips))
    eval_bloom(ips, 3, 10 * length(ips))
    eval_bloom(ips, 4, 10 * length(ips))
    eval_bloom(ips, 5, 10 * length(ips))
    eval_bloom(ips, 6, 10 * length(ips))
    eval_bloom(ips, 7, 10 * length(ips))
    eval_bloom(ips, 8, 10 * length(ips))
    eval_bloom(ips, 9, 10 * length(ips))
    eval_bloom(ips, 10, 10 * length(ips))
end

"""
    bloom_plots()

Plots both the capacity and error rate for a Bloom filter
"""
function bloom_plots()
    function false_pos_rate(k::Int64, α::Float64)
        return ((1.0 - exp(-k * α))^k)
    end

    # plot the false positive rate as a function of independent hash-functions
    p = plot(1:20, map(k -> false_pos_rate(k, 0.1), 1:20), legend = false, linewidth = 3)
    scatter!(1:20, map(k -> false_pos_rate(k, 0.1), 1:20))
    ylabel!("P(False Positive)")
    xlabel!("J")
    display(p)

    # plot the false positive rate as a function of the ratio of keys to filter size
    αs = range(0.0, 0.5, 100)
    p = plot(αs, map(α -> false_pos_rate(10, α), αs), legend = false, linewidth = 3)
    scatter!(αs, map(α -> false_pos_rate(10, α), αs))
    ylabel!("P(False Positive)")
    xlabel!("α")
    display(p)


end


# main entry of the program
if (length(ARGS) == 1)
    demo_bloom(ARGS[1])
else
    bloom_plots()
end
