#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>

class RoundedRectangleShape : public sf::Shape {
public:
    // Constructor
    RoundedRectangleShape(const sf::Vector2f& size = {0.f, 0.f}, float radius = 0.f, std::size_t cornerPointCount = 8)
        : m_size(size), m_radius(radius), m_cornerPointCount(std::max<std::size_t>(1, cornerPointCount))
    {
        update();  // Cập nhật lại hình khi khởi tạo
    }

    // Setters and getters
    void setSize(const sf::Vector2f& size) { m_size = size; update(); }
    sf::Vector2f getSize() const { return m_size; }

    void setCornerRadius(float radius) { m_radius = std::max(0.f, radius); update(); }
    float getCornerRadius() const { return m_radius; }

    void setCornerPointCount(std::size_t count) { m_cornerPointCount = std::max<std::size_t>(1, count); update(); }
    std::size_t getCornerPointCount() const { return m_cornerPointCount; }

    // Hàm ghi đè getLocalBounds để trả về bounding box trong không gian cục bộ
    virtual sf::FloatRect getLocalBounds() const {
        return sf::FloatRect(0.f, 0.f, m_size.x, m_size.y); // Đơn giản hóa: trả về m_size
    }

    // Hàm trả về bounding box toàn cầu (vị trí thực của box)
    sf::FloatRect getGlobalBounds() const {
        return getTransform().transformRect(getLocalBounds()); // Áp dụng transform vào bounding box
    }

    // sf::Shape overrides
    virtual std::size_t getPointCount() const override {
        return m_cornerPointCount * 4;  // Mỗi góc có số điểm tương ứng
    }

    virtual sf::Vector2f getPoint(std::size_t index) const override {
        static const float PI = 3.14159265358979323846f;
        const std::size_t ptsPerCorner = m_cornerPointCount;
        const float angleStep = (PI / 2.f) / (ptsPerCorner - 1); // Chia góc 90 độ thành các điểm

        std::size_t corner = index / ptsPerCorner; // 0-3: các góc
        std::size_t iInCorner = index % ptsPerCorner; // Các điểm trong một góc

        float startAngle = 0.f;
        sf::Vector2f center;

        // Các góc của hình chữ nhật bo tròn
        switch (corner) {
            case 0: // Top-left
                center = { m_radius, m_radius };
                startAngle = PI;            // 180 deg
                break;
            case 1: // Top-right
                center = { m_size.x - m_radius, m_radius };
                startAngle = -PI / 2.f;     // -90 deg
                break;
            case 2: // Bottom-right
                center = { m_size.x - m_radius, m_size.y - m_radius };
                startAngle = 0.f;           // 0 deg
                break;
            case 3: // Bottom-left
            default:
                center = { m_radius, m_size.y - m_radius };
                startAngle = PI / 2.f;      // 90 deg
                break;
        }

        float angle = startAngle + angleStep * static_cast<float>(iInCorner);
        float x = center.x + std::cos(angle) * m_radius;
        float y = center.y + std::sin(angle) * m_radius;
        return { x, y };
    }
    bool contains(sf::Vector2f point) const {
        // Kiểm tra nếu điểm nằm trong hình chữ nhật chính (ngoài các góc bo tròn)
        if (point.x >= 0.f && point.x <= m_size.x && point.y >= 0.f && point.y <= m_size.y) {
            // Kiểm tra góc bo tròn: 4 góc
            if (point.x >= m_radius && point.x <= m_size.x - m_radius && 
                point.y >= m_radius && point.y <= m_size.y - m_radius) {
                return true;
            }

            // Kiểm tra các góc bo tròn (Top-left, Top-right, Bottom-left, Bottom-right)
            static const float PI = 3.14159265358979323846f;
            const std::size_t ptsPerCorner = m_cornerPointCount;
            const float angleStep = (PI / 2.f) / (ptsPerCorner - 1);

            for (std::size_t corner = 0; corner < 4; ++corner) {
                sf::Vector2f center;
                float startAngle = 0.f;

                switch (corner) {
                    case 0: // Top-left
                        center = { m_radius, m_radius };
                        startAngle = PI; // 180 deg
                        break;
                    case 1: // Top-right
                        center = { m_size.x - m_radius, m_radius };
                        startAngle = -PI / 2.f; // -90 deg
                        break;
                    case 2: // Bottom-right
                        center = { m_size.x - m_radius, m_size.y - m_radius };
                        startAngle = 0.f; // 0 deg
                        break;
                    case 3: // Bottom-left
                        center = { m_radius, m_size.y - m_radius };
                        startAngle = PI / 2.f; // 90 deg
                        break;
                }

                // Xác định góc của các điểm trong góc bo tròn
                for (std::size_t iInCorner = 0; iInCorner < ptsPerCorner; ++iInCorner) {
                    float angle = startAngle + angleStep * iInCorner;
                    float x = center.x + std::cos(angle) * m_radius;
                    float y = center.y + std::sin(angle) * m_radius;

                    // Kiểm tra nếu điểm nằm trong vùng bo tròn của góc
                    if (std::hypot(point.x - x, point.y - y) <= m_radius) {
                        return true;
                    }
                }
            }
        }

        return false;
    }


private:
    sf::Vector2f m_size;  // Kích thước của hình chữ nhật
    float m_radius;       // Bán kính bo góc
    std::size_t m_cornerPointCount; // Số điểm ở mỗi góc
};