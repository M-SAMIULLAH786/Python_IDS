def compute_safety(data):
    scores = {}

    for d in data:
        b = d["bid"]
        units = d["units"]
        alerts = 0 if d["alerts"][0] == "None" else len(d["alerts"])

        score = max(100 - units - (alerts * 15), 0)
        scores[b] = score

    return scores


if __name__ == "__main__":
    sample = [
        {"bid": "301", "units": 45, "alerts": ["None"]},
        {"bid": "302", "units": 120, "alerts": ["Overload"]},
    ]
    print(compute_safety(sample))
