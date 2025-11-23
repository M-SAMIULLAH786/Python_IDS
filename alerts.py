def count_alerts(data):
    alert_counts = {}

    for d in data:
        for a in d["alerts"]:
            if a != "None":
                alert_counts[a] = alert_counts.get(a, 0) + 1

    return alert_counts


if __name__ == "__main__":
    sample = [
        {"alerts": ["None"]},
        {"alerts": ["Overload"]},
        {"alerts": ["FireRisk"]},
    ]
    print(count_alerts(sample))
