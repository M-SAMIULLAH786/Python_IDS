# ==============================
# Problem Set: Traffic Data Analysis (4–5 Separate Python Files)
# ==============================
# This canvas contains **5 Python files**, each implementing
# a similar IoT/Traffic analytics problem.
# Copy each section into its own .py file.

# --------------------------------------------------------------
# FILE 1: parser.py — Parse Raw Logs into Structured Data
# --------------------------------------------------------------

def parse_logs(raw_logs):
    parsed = []
    for log in raw_logs:
        parts = log.split(',')
        entry = {}
        for p in parts:
            key, value = p.split(':', 1)
            if key == 'speed':
                value = int(value)
            if key == 'violations':
                value = value.strip('[]').split(',')
            entry[key] = value
        parsed.append(entry)
    return parsed

if __name__ == "__main__":
    logs = [
        "id:501,zone:A1,vehicle:Car,speed:62,time:08:30,violations:[None],status:Smooth",
        "id:502,zone:A1,vehicle:Bike,speed:85,time:09:10,violations:[Helmet],status:Busy",
    ]
    print(parse_logs(logs))


# --------------------------------------------------------------
# FILE 2: zone_speed.py — Calculate Average Speed per Zone
# --------------------------------------------------------------

def avg_speed_by_zone(data):
    zones = {}
    for d in data:
        zone = d['zone']
        zones.setdefault(zone, []).append(d['speed'])
    return {z: sum(v)/len(v) for z, v in zones.items()}

if __name__ == "__main__":
    sample = [
        {'zone': 'A1', 'speed': 62},
        {'zone': 'A1', 'speed': 85},
        {'zone': 'B2', 'speed': 45},
    ]
    print(avg_speed_by_zone(sample))


# --------------------------------------------------------------
# FILE 3: peak_hour.py — Determine Peak Hour
# --------------------------------------------------------------

def peak_hour(data):
    hours = {}
    for d in data:
        hour = d['time'].split(':')[0]
        hours[hour] = hours.get(hour, 0) + 1
    return max(hours, key=hours.get)

if __name__ == "__main__":
    sample = [
        {'time': '08:30'},
        {'time': '09:10'},
        {'time': '17:25'},
    ]
    print(peak_hour(sample))


# --------------------------------------------------------------
# FILE 4: violations.py — Count Violation Types
# --------------------------------------------------------------

def count_violations(data):
    vcount = {}
    for d in data:
        for v in d['violations']:
            if v != 'None':
                vcount[v] = vcount.get(v, 0) + 1
    return vcount

if __name__ == "__main__":
    sample = [
        {'violations': ['None']},
        {'violations': ['Helmet']},
        {'violations': ['Overspeed']},
    ]
    print(count_violations(sample))


# --------------------------------------------------------------
# FILE 5: safety_index.py — Compute Safety Index per Zone
# --------------------------------------------------------------

def safety_index(data):
    zone_stats = {}
    for d in data:
        z = d['zone']
        zone_stats.setdefault(z, {'speed': [], 'violations': 0})
        zone_stats[z]['speed'].append(d['speed'])
        if d['violations'][0] != 'None':
            zone_stats[z]['violations'] += 1

    result = {}
    for z, stats in zone_stats.items():
        avg_speed = sum(stats['speed']) / len(stats['speed'])
        score = 100 - avg_speed - (stats['violations'] * 10)
        result[z] = max(score, 0)
    return result

if __name__ == "__main__":
    sample = [
        {'zone': 'A1', 'speed': 62, 'violations': ['None']},
        {'zone': 'A1', 'speed': 85, 'violations': ['Helmet']},
    ]
    print(safety_index(sample))
