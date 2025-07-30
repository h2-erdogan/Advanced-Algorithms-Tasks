import csv
import heapq

# for graph demos
graph = {}

# to get data 
with open('task1_3_data.csv', 'r') as file:
    reader = csv.reader(file)
    for row in reader:
        station1 = row[0].strip().lower()
        station2 = row[1].strip().lower()
        cost = int(row[2])
        time = int(row[3])
        graph.setdefault(station1, {})[station2] = (cost, time)
        graph.setdefault(station2, {})[station1] = (cost, time)

# Dijkstra algorithm
def dijkstra(start, end, weight_type='cost'):
    queue = []
    heapq.heappush(queue, (0, start, []))  # (total_weight, current_station, path)

    visited = set()
    while queue:
        total_weight, station, path = heapq.heappop(queue)
        if station in visited:
            continue
        visited.add(station)
        path = path + [station]
        if station == end:
            return total_weight, path
        for neighbor, (cost, time) in graph[station].items():
            if neighbor not in visited:
                weight = cost if weight_type == 'cost' else time
                heapq.heappush(queue, (total_weight + weight, neighbor, path))
    return float('inf'), []


def main():
    print("Welcome to the Train Ticket Search System!")
    departure = input("Enter departure station: ").strip().lower()
    destination = input("Enter destination station: ").strip().lower()
    print("Do you want to search by:\n1. Cheapest Ticket\n2. Fastest Journey")
    choice = input("Enter 1 or 2: ")

    if departure not in graph or destination not in graph:
        print("\nInvalid station names. Please try again.")
        print("\nAvailable stations:")
        for station in graph.keys():
            print(f"- {station.title()}")
        return

    weight_type = 'cost' if choice == '1' else 'time'
    total_weight, path = dijkstra(departure, destination, weight_type)
    
    if total_weight == float('inf'):
        print("No route found.")
    else:
        if weight_type == 'cost':
            print(f"\nCheapest Ticket Cost: £{total_weight}")
        else:
            print(f"\nFastest Journey Time: {total_weight} minutes")
        print(f"Route: {' -> '.join([s.title() for s in path])}")

if __name__ == "__main__":
    main()
