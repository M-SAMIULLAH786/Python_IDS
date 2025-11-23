def avg_units_by_type(data):
    stats = {}

    for d in data:
        btype = d["type"]
        stats.setdefault(btype, []).append(d["units"])

    return {t: sum(v)/len(v) for t, v in stats.items()}


if __name__ == "__main__":
    sample = [
        {"type": "Home", "units": 45},
        {"type": "Home", "units": 65},
        {"type": "Office", "units": 120},
    ]
    print(avg_units_by_type(sample))
