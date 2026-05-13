#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <optional>
#include <iostream>
#include <string>
#define VERDE "\033[32m"

int main() {
    // SFML 3: La ventana se inicializa con sf::VideoMode y un objeto de tamaño
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Circulo 30 Segundos - SFML 3");
    window.setFramerateLimit(60);

    const float radius = 200.f;
    const float radius2 = 150.f; // Radio del círculo interior para un efecto de anillo
    const sf::Vector2f center{400.f, 300.f};
    const sf::Vector2f center2{400.f, 300.f}; // Centro del círculo interior
    const float duration = 30.f; // Tiempo para completar el círculo
    const int totalPoints = 500; // Mayor resolución para un borde suave
    const float PI = 3.14159265359f;
    sf::CircleShape innerCircle(radius2);
    innerCircle.setFillColor(sf::Color::Transparent);
    innerCircle.setOutlineColor(sf::Color::White);
    innerCircle.setOutlineThickness(2.f);
    innerCircle.setPosition({center2.x - radius2, center2.y - radius2});
    
    
    sf::Clock clock;
    
    while (window.isOpen()) {
        // SFML 3: Nuevo sistema de eventos basado en std::optional
        while (const std::optional event = window.pollEvent()) { // Cambiado a std::optional
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        
        // 1. Calcular el progreso basado en el tiempo (0.0 a 1.0)
        float elapsed = clock.getElapsedTime().asSeconds();
        if (elapsed > duration) {
            clock.restart();
            elapsed = 0.0f;
        }
        
        float progress = elapsed / duration;
        
        // 2. Crear el perímetro usando un VertexArray de tipo LineStrip
        sf::VertexArray perimeter(sf::PrimitiveType::LineStrip);
        
        // Calculamos cuántos puntos dibujar según el progreso actual
        int pointsToShow = static_cast<int>(progress * totalPoints);
        
        for (int i = 0; i <= pointsToShow; ++i) {
            // El ángulo se calcula para que 1.0 de progreso sea 2*PI (360 grados)
            // Restamos PI/2 para que el dibujo comience en la parte superior
            float angle = (i * 2.f * PI / totalPoints) - (PI / 2.f);
            
            float x = center.x + radius * std::cos(angle);
            float y = center.y + radius * std::sin(angle);

            // SFML 3: Inicialización de vértice usando nombres de campos (Designated Initializers)
            perimeter.append(sf::Vertex{
                .position = {x, y}, 
                .color = sf::Color::Red
            });
        }
        
        // 3. Renderizado
        window.clear(sf::Color::Black);
        
        if (perimeter.getVertexCount() > 1) {
            window.draw(perimeter);
        }

        if(clock.getElapsedTime().asSeconds() >=1.0f){
            if(progress < 1.0f){
                progress += 0.1f;
                if(progress > 1.0f){
                    progress = 1.0f;
                }
                std::cout << VERDE << "Dibujando círculo: " << static_cast<int>(progress * 100) << "% completo" << std::endl;
            }

        }
        
        window.draw(innerCircle);
        window.display();
    }

    return 0;
}