def parse_energy_logs(raw_logs):
    parsed = []
    for log in raw_logs:
        parts = log.split(",")
        entry = {}
        for p in parts:
            key, value = p.split(":", 1)

            if key == "units":
                value = int(value)

            if key == "alerts":
                value = value.strip("[]").split(",")

            entry[key] = value
        parsed.append(entry)

    return parsed


if __name__ == "__main__":
    logs = [
        "bid:301,type:Home,units:45,time:07:20,status:Normal,alerts:[None]"
    ]
    print(parse_energy_logs(logs))
