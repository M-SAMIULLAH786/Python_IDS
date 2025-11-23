def peak_usage_hour(data):
    hours = {}

    for d in data:
        hour = d["time"].split(":")[0]
        hours[hour] = hours.get(hour, 0) + d["units"]

    return max(hours, key=hours.get)


if __name__ == "__main__":
    sample = [
        {"time": "07:20", "units": 45},
        {"time": "11:10", "units": 120},
        {"time": "18:45", "units": 350},
    ]
    print(peak_usage_hour(sample))
