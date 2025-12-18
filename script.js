// ===================================
// WAIT FOR DOM TO LOAD
// ===================================
window.addEventListener('DOMContentLoaded', function() {

// ===================================
// PARTICLE.JS CONFIGURATION
// ===================================
if (typeof particlesJS !== 'undefined') {
    particlesJS('particles-js', {
        particles: {
            number: {
                value: 80,
                density: {
                    enable: true,
                    value_area: 800
                }
            },
            color: {
                value: '#6366f1'
            },
            shape: {
                type: 'circle',
            },
            opacity: {
                value: 0.5,
                random: false,
            },
            size: {
                value: 3,
                random: true,
            },
            line_linked: {
                enable: true,
                distance: 150,
                color: '#6366f1',
                opacity: 0.4,
                width: 1
            },
            move: {
                enable: true,
                speed: 2,
                direction: 'none',
                random: false,
                straight: false,
                out_mode: 'out',
                bounce: false,
            }
        },
        interactivity: {
            detect_on: 'canvas',
            events: {
                onhover: {
                    enable: true,
                    mode: 'grab'
                },
                onclick: {
                    enable: true,
                    mode: 'push'
                },
                resize: true
            },
            modes: {
                grab: {
                    distance: 140,
                    line_linked: {
                        opacity: 1
                    }
                },
                push: {
                    particles_nb: 4
                }
            }
        },
        retina_detect: true
    });
}

// ===================================
// CUSTOM CURSOR
// ===================================
const cursorDot = document.querySelector('[data-cursor-dot]');
const cursorOutline = document.querySelector('[data-cursor-outline]');

let mouseX = 0, mouseY = 0;
let outlineX = 0, outlineY = 0;
const trail = [];
const trailLength = 20;

window.addEventListener('mousemove', (e) => {
    mouseX = e.clientX;
    mouseY = e.clientY;
    
    cursorDot.style.left = `${e.clientX}px`;
    cursorDot.style.top = `${e.clientY}px`;
    
    // Add trail effect
    trail.push({ x: e.clientX, y: e.clientY, time: Date.now() });
    if (trail.length > trailLength) trail.shift();
    
    // Create sparkle on movement
    if (Math.random() > 0.95) {
        createSparkle(e.clientX, e.clientY);
    }
});

function createSparkle(x, y) {
    const sparkle = document.createElement('div');
    sparkle.style.cssText = `
        position: fixed;
        width: 4px;
        height: 4px;
        background: radial-gradient(circle, #6366f1, transparent);
        border-radius: 50%;
        pointer-events: none;
        z-index: 9998;
        left: ${x}px;
        top: ${y}px;
        animation: sparkleAnim 1s ease-out forwards;
    `;
    document.body.appendChild(sparkle);
    setTimeout(() => sparkle.remove(), 1000);
}

const sparkleStyle = document.createElement('style');
sparkleStyle.textContent = `
    @keyframes sparkleAnim {
        0% { transform: scale(0); opacity: 1; }
        50% { transform: scale(1.5); opacity: 0.5; }
        100% { transform: scale(0); opacity: 0; }
    }
`;
document.head.appendChild(sparkleStyle);

function animateOutline() {
    outlineX += (mouseX - outlineX) * 0.15;
    outlineY += (mouseY - outlineY) * 0.15;
    
    cursorOutline.style.left = `${outlineX}px`;
    cursorOutline.style.top = `${outlineY}px`;
    
    requestAnimationFrame(animateOutline);
}
animateOutline();

// Cursor effects on interactive elements
document.querySelectorAll('a, button, .btn').forEach(el => {
    el.addEventListener('mouseenter', () => {
        cursorOutline.style.transform = 'translate(-50%, -50%) scale(1.5)';
    });
    el.addEventListener('mouseleave', () => {
        cursorOutline.style.transform = 'translate(-50%, -50%) scale(1)';
    });
});

// Magnetic effect for buttons
document.querySelectorAll('.btn, .project-link').forEach(btn => {
    btn.addEventListener('mousemove', (e) => {
        const rect = btn.getBoundingClientRect();
        const x = e.clientX - rect.left - rect.width / 2;
        const y = e.clientY - rect.top - rect.height / 2;
        
        btn.style.transform = `translate(${x * 0.2}px, ${y * 0.2}px)`;
    });
    
    btn.addEventListener('mouseleave', () => {
        btn.style.transform = 'translate(0, 0)';
    });
});

// ===================================
// NAVIGATION
// ===================================
const navbar = document.getElementById('navbar');
const hamburger = document.getElementById('hamburger');
const navMenu = document.getElementById('nav-menu');
const navLinks = document.querySelectorAll('.nav-link');

// Navbar scroll effect
window.addEventListener('scroll', () => {
    if (window.scrollY > 50) {
        navbar.classList.add('scrolled');
    } else {
        navbar.classList.remove('scrolled');
    }
    
    // Dynamic color theme based on section
    updateThemeColor();
});

function updateThemeColor() {
    const sections = ['home', 'about', 'skills', 'experience', 'projects', 'education', 'contact'];
    const colors = ['#6366f1', '#a855f7', '#ec4899', '#f59e0b', '#22c55e', '#3b82f6', '#8b5cf6'];
    
    sections.forEach((section, index) => {
        const element = document.getElementById(section);
        if (element) {
            const rect = element.getBoundingClientRect();
            if (rect.top <= 100 && rect.bottom >= 100) {
                document.documentElement.style.setProperty('--primary-color', colors[index]);
            }
        }
    });
}

// Mobile menu toggle
hamburger.addEventListener('click', () => {
    hamburger.classList.toggle('active');
    navMenu.classList.toggle('active');
});

// Close mobile menu on link click
navLinks.forEach(link => {
    link.addEventListener('click', () => {
        hamburger.classList.remove('active');
        navMenu.classList.remove('active');
    });
});

// Active navigation link on scroll
window.addEventListener('scroll', () => {
    let current = '';
    const sections = document.querySelectorAll('section');
    
    sections.forEach(section => {
        const sectionTop = section.offsetTop;
        const sectionHeight = section.clientHeight;
        if (scrollY >= (sectionTop - 200)) {
            current = section.getAttribute('id');
        }
    });
    
    navLinks.forEach(link => {
        link.classList.remove('active');
        if (link.getAttribute('href').slice(1) === current) {
            link.classList.add('active');
        }
    });
});

// ===================================
// TYPING EFFECT
// ===================================
const typedTextSpan = document.querySelector('.typed-text');
const cursorSpan = document.querySelector('.cursor');

const textArray = [
    'Software Developer',
    'React Native Specialist',
    'Problem Solver',
    'Web Developer',
    'Full Stack Engineer',
    'Open for Remote Work'
];
const typingDelay = 100;
const erasingDelay = 50;
const newTextDelay = 2000;
let textArrayIndex = 0;
let charIndex = 0;

function type() {
    if (charIndex < textArray[textArrayIndex].length) {
        typedTextSpan.textContent += textArray[textArrayIndex].charAt(charIndex);
        charIndex++;
        
        // Visual feedback for typing
        typedTextSpan.style.transform = 'scale(1.02)';
        setTimeout(() => {
            typedTextSpan.style.transform = 'scale(1)';
        }, 50);
        
        setTimeout(type, typingDelay);
    } else {
        setTimeout(erase, newTextDelay);
    }
}

function erase() {
    if (charIndex > 0) {
        typedTextSpan.textContent = textArray[textArrayIndex].substring(0, charIndex - 1);
        charIndex--;
        setTimeout(erase, erasingDelay);
    } else {
        textArrayIndex++;
        if (textArrayIndex >= textArray.length) textArrayIndex = 0;
        setTimeout(type, typingDelay + 500);
    }
}

// Start typing effect
document.addEventListener('DOMContentLoaded', () => {
    setTimeout(type, newTextDelay + 250);
    
    // Text scramble effect for name
    const nameElement = document.querySelector('.name .highlight');
    if (nameElement) {
        scrambleText(nameElement, nameElement.textContent);
    }
});

function scrambleText(element, finalText) {
    const chars = '!@#$%^&*()_+-=[]{}|;:,.<>?';
    let iteration = 0;
    const interval = setInterval(() => {
        element.textContent = finalText
            .split('')
            .map((char, index) => {
                if (index < iteration) {
                    return finalText[index];
                }
                return chars[Math.floor(Math.random() * chars.length)];
            })
            .join('');
        
        if (iteration >= finalText.length) {
            clearInterval(interval);
        }
        iteration += 1 / 3;
    }, 30);
}

// ===================================
// SCROLL ANIMATIONS
// ===================================
const observerOptions = {
    threshold: 0.1,
    rootMargin: '0px 0px -100px 0px'
};

const observer = new IntersectionObserver((entries) => {
    entries.forEach((entry, index) => {
        if (entry.isIntersecting) {
            setTimeout(() => {
                entry.target.classList.add('visible');
            }, index * 100);
            
            // Animate skill bars when in view
            if (entry.target.classList.contains('skill-card')) {
                const skillBar = entry.target.querySelector('.skill-bar');
                const level = skillBar.getAttribute('data-level');
                setTimeout(() => {
                    skillBar.style.width = level + '%';
                }, 200);
            }
        }
    });
}, observerOptions);

// Observe all sections and cards
document.querySelectorAll('section > .container, .skill-card, .project-card, .education-card, .timeline-item').forEach((el, index) => {
    el.classList.add('fade-in');
    el.style.animationDelay = `${index * 0.1}s`;
    observer.observe(el);
});

// Add hover sound effect simulation
document.querySelectorAll('.btn, .project-card, .skill-card').forEach(el => {
    el.addEventListener('mouseenter', () => {
        el.style.animation = 'bounceIn 0.5s ease-out';
    });
    el.addEventListener('animationend', () => {
        el.style.animation = '';
    });
});

const bounceStyle = document.createElement('style');
bounceStyle.textContent = `
    @keyframes bounceIn {
        0% { transform: scale(1); }
        25% { transform: scale(0.95); }
        50% { transform: scale(1.05); }
        75% { transform: scale(0.98); }
        100% { transform: scale(1); }
    }
`;
document.head.appendChild(bounceStyle);

// ===================================
// SMOOTH SCROLLING
// ===================================
document.querySelectorAll('a[href^="#"]').forEach(anchor => {
    anchor.addEventListener('click', function (e) {
        const href = this.getAttribute('href');
        
        // Skip if href is just "#"
        if (href === '#' || href === '#home') {
            if (href === '#home') {
                e.preventDefault();
                window.scrollTo({ top: 0, behavior: 'smooth' });
            }
            return;
        }
        
        e.preventDefault();
        const target = document.querySelector(href);
        
        if (target) {
            const navbar = document.querySelector('.navbar');
            const navbarHeight = navbar ? navbar.offsetHeight : 80;
            const targetPosition = target.getBoundingClientRect().top + window.pageYOffset - navbarHeight - 20;
            
            window.scrollTo({
                top: targetPosition,
                behavior: 'smooth'
            });
        }
    });
});

// ===================================
// CONTACT FORM
// ===================================
const contactForm = document.getElementById('contact-form');

contactForm.addEventListener('submit', (e) => {
    e.preventDefault();
    
    // Get form data
    const formData = new FormData(contactForm);
    const data = Object.fromEntries(formData);
    
    // Simulate form submission
    const submitBtn = contactForm.querySelector('.btn-submit');
    const originalText = submitBtn.innerHTML;
    
    submitBtn.innerHTML = '<span>Sending...</span><i class="fas fa-spinner fa-spin"></i>';
    submitBtn.disabled = true;
    
    setTimeout(() => {
        submitBtn.innerHTML = '<span>Sent Successfully!</span><i class="fas fa-check"></i>';
        
        setTimeout(() => {
            submitBtn.innerHTML = originalText;
            submitBtn.disabled = false;
            contactForm.reset();
            
            // Show success message
            showNotification('Message sent successfully! I will get back to you soon.');
        }, 2000);
    }, 2000);
});

// ===================================
// NOTIFICATION SYSTEM
// ===================================
function showNotification(message) {
    const notification = document.createElement('div');
    notification.style.cssText = `
        position: fixed;
        top: 100px;
        right: 20px;
        background: linear-gradient(135deg, #6366f1, #a855f7);
        color: white;
        padding: 1rem 2rem;
        border-radius: 10px;
        box-shadow: 0 10px 40px rgba(0, 0, 0, 0.3);
        z-index: 10001;
        animation: slideInRight 0.5s ease-out;
        display: flex;
        align-items: center;
        gap: 1rem;
        max-width: 400px;
    `;
    
    notification.innerHTML = `
        <i class="fas fa-check-circle"></i>
        <span>${message}</span>
    `;
    
    document.body.appendChild(notification);
    
    setTimeout(() => {
        notification.style.animation = 'slideOutRight 0.5s ease-out';
        setTimeout(() => notification.remove(), 500);
    }, 3000);
}

// Add animation keyframes
const style = document.createElement('style');
style.textContent = `
    @keyframes slideInRight {
        from {
            transform: translateX(400px);
            opacity: 0;
        }
        to {
            transform: translateX(0);
            opacity: 1;
        }
    }
    
    @keyframes slideOutRight {
        from {
            transform: translateX(0);
            opacity: 1;
        }
        to {
            transform: translateX(400px);
            opacity: 0;
        }
    }
`;
document.head.appendChild(style);

// ===================================
// PARALLAX EFFECT
// ===================================
let ticking = false;
let lastScrollY = 0;

window.addEventListener('scroll', () => {
    lastScrollY = window.pageYOffset;
    
    if (!ticking) {
        window.requestAnimationFrame(() => {
            const scrolled = lastScrollY;
            const parallaxElements = document.querySelectorAll('.hero-image, .about-img-wrapper');
            
            parallaxElements.forEach(el => {
                const speed = 0.5;
                el.style.transform = `translateY(${scrolled * speed}px)`;
            });
            
            // Add rotation effect to rotating border
            const rotatingBorder = document.querySelector('.rotating-border');
            if (rotatingBorder) {
                rotatingBorder.style.transform = `rotate(${scrolled * 0.2}deg)`;
            }
            
            ticking = false;
        });
        
        ticking = true;
    }
});

// ===================================
// IMAGE LOADING
// ===================================
window.addEventListener('load', () => {
    document.body.classList.add('loaded');
});

// ===================================
// COUNTER ANIMATION FOR STATS
// ===================================
function animateCounter(element, target, duration = 2000) {
    let start = 0;
    const increment = target / (duration / 16);
    
    const timer = setInterval(() => {
        start += increment;
        if (start >= target) {
            element.textContent = target;
            clearInterval(timer);
        } else {
            element.textContent = Math.floor(start);
        }
    }, 16);
}

// Observe stats for counter animation
const statsObserver = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
        if (entry.isIntersecting) {
            const percentage = entry.target.querySelector('.skill-percentage');
            if (percentage && !percentage.classList.contains('animated')) {
                percentage.classList.add('animated');
                const value = parseInt(percentage.textContent);
                percentage.textContent = '0%';
                
                let start = 0;
                const timer = setInterval(() => {
                    start++;
                    percentage.textContent = start + '%';
                    if (start >= value) {
                        clearInterval(timer);
                    }
                }, 20);
            }
        }
    });
}, { threshold: 0.5 });

document.querySelectorAll('.skill-card').forEach(card => {
    statsObserver.observe(card);
});

// ===================================
// FLOATING ANIMATION FOR CARDS
// ===================================
document.querySelectorAll('.floating-card').forEach((card, index) => {
    card.style.animation = `floatCard 3s ease-in-out infinite`;
    card.style.animationDelay = `${index * 1.5}s`;
});

// Add continuous floating to project cards
document.querySelectorAll('.project-card').forEach((card, index) => {
    setInterval(() => {
        card.style.animation = 'cardFloat 4s ease-in-out';
        setTimeout(() => {
            card.style.animation = '';
        }, 4000);
    }, 8000 + (index * 2000));
});

// ===================================
// TILT EFFECT ON CARDS
// ===================================
const cards = document.querySelectorAll('.skill-card, .project-card, .education-card');

cards.forEach(card => {
    card.addEventListener('mousemove', (e) => {
        const rect = card.getBoundingClientRect();
        const x = e.clientX - rect.left;
        const y = e.clientY - rect.top;
        
        const centerX = rect.width / 2;
        const centerY = rect.height / 2;
        
        const rotateX = (y - centerY) / 10;
        const rotateY = (centerX - x) / 10;
        
        card.style.transform = `perspective(1000px) rotateX(${rotateX}deg) rotateY(${rotateY}deg) translateY(-10px) scale(1.02)`;
        card.style.boxShadow = `${-rotateY}px ${rotateX}px 40px rgba(99, 102, 241, 0.3)`;
        
        // Add light reflection
        const highlight = card.querySelector('.card-highlight') || createHighlight(card);
        highlight.style.background = `radial-gradient(circle at ${x}px ${y}px, rgba(255,255,255,0.2), transparent)`;
    });
    
    card.addEventListener('mouseleave', () => {
        card.style.transform = 'perspective(1000px) rotateX(0) rotateY(0) translateY(0) scale(1)';
        card.style.boxShadow = '';
        const highlight = card.querySelector('.card-highlight');
        if (highlight) highlight.style.background = 'transparent';
    });
});

function createHighlight(card) {
    const highlight = document.createElement('div');
    highlight.className = 'card-highlight';
    highlight.style.cssText = `
        position: absolute;
        top: 0;
        left: 0;
        width: 100%;
        height: 100%;
        pointer-events: none;
        border-radius: inherit;
        transition: background 0.1s ease;
    `;
    card.appendChild(highlight);
    return highlight;
}

// ===================================
// SCROLL TO TOP BUTTON
// ===================================
const scrollTopBtn = document.createElement('button');
scrollTopBtn.innerHTML = '<i class="fas fa-arrow-up"></i>';
scrollTopBtn.className = 'scroll-top-btn';
scrollTopBtn.style.cssText = `
    position: fixed;
    bottom: 30px;
    right: 30px;
    width: 50px;
    height: 50px;
    background: linear-gradient(135deg, #6366f1, #a855f7);
    border: none;
    border-radius: 50%;
    color: white;
    font-size: 1.2rem;
    cursor: pointer;
    opacity: 0;
    visibility: hidden;
    transition: all 0.4s cubic-bezier(0.4, 0, 0.2, 1);
    z-index: 1000;
    box-shadow: 0 10px 40px rgba(0, 0, 0, 0.3);
`;

document.body.appendChild(scrollTopBtn);

window.addEventListener('scroll', () => {
    if (window.pageYOffset > 500) {
        scrollTopBtn.style.opacity = '1';
        scrollTopBtn.style.visibility = 'visible';
    } else {
        scrollTopBtn.style.opacity = '0';
        scrollTopBtn.style.visibility = 'hidden';
    }
});

scrollTopBtn.addEventListener('click', () => {
    window.scrollTo({
        top: 0,
        behavior: 'smooth'
    });
});

scrollTopBtn.addEventListener('mouseenter', () => {
    scrollTopBtn.style.transform = 'scale(1.1)';
});

scrollTopBtn.addEventListener('mouseleave', () => {
    scrollTopBtn.style.transform = 'scale(1)';
});

// ===================================
// PRELOADER
// ===================================
window.addEventListener('load', () => {
    const loadingScreen = document.getElementById('loadingScreen');
    
    setTimeout(() => {
        loadingScreen.classList.add('hidden');
        setTimeout(() => loadingScreen.remove(), 500);
        
        // Add entry animation to body
        document.body.style.animation = 'none';
        document.body.style.opacity = '1';
    }, 2500);
});

// ===================================
// RESIZE HANDLER
// ===================================
let resizeTimer;
window.addEventListener('resize', () => {
    clearTimeout(resizeTimer);
    resizeTimer = setTimeout(() => {
        // Reinitialize particles on resize
        particlesJS('particles-js', {
            particles: {
                number: {
                    value: window.innerWidth < 768 ? 40 : 80,
                    density: {
                        enable: true,
                        value_area: 800
                    }
                },
                color: {
                    value: '#6366f1'
                },
                shape: {
                    type: 'circle',
                },
                opacity: {
                    value: 0.5,
                    random: false,
                },
                size: {
                    value: 3,
                    random: true,
                },
                line_linked: {
                    enable: true,
                    distance: 150,
                    color: '#6366f1',
                    opacity: 0.4,
                    width: 1
                },
                move: {
                    enable: true,
                    speed: 2,
                    direction: 'none',
                    random: false,
                    straight: false,
                    out_mode: 'out',
                    bounce: false,
                }
            },
            interactivity: {
                detect_on: 'canvas',
                events: {
                    onhover: {
                        enable: true,
                        mode: 'grab'
                    },
                    onclick: {
                        enable: true,
                        mode: 'push'
                    },
                    resize: true
                }
            },
            retina_detect: true
        });
    }, 250);
});

// ===================================
// CONSOLE EASTER EGG
// ===================================
console.clear();
console.log('%c', 'font-size: 1px; padding: 100px 150px; background: url("https://media.giphy.com/media/3o7abKhOpu0NwenH3O/giphy.gif") no-repeat; background-size: contain;');
console.log('%c👋 Hello Developer!', 'color: #6366f1; font-size: 24px; font-weight: bold; text-shadow: 2px 2px 4px rgba(0,0,0,0.3);');
console.log('%cLooking for something? Feel free to reach out!', 'color: #a855f7; font-size: 16px;');
console.log('%c📧 sami.suu1506@gmail.com', 'color: #ec4899; font-size: 14px;');
console.log('%c💼 LinkedIn: https://www.linkedin.com/in/muhamamd-samiullah-403178394/', 'color: #22c55e; font-size: 14px;');
console.log('%c💻 GitHub: https://github.com/M-SAMIULLAH786', 'color: #3b82f6; font-size: 14px;');
console.log('%c\n🎨 Portfolio Stats:', 'color: #f59e0b; font-size: 16px; font-weight: bold;');
console.table({
    'Lines of Code': '2500+',
    'Animations': '20+',
    'Projects': '8',
    'Technologies': '15+',
    'Internships': '2',
    'Passion': '100%'
});

// ===================================
// PERFORMANCE OPTIMIZATION
// ===================================
// Lazy load images if any
if ('IntersectionObserver' in window) {
    const imageObserver = new IntersectionObserver((entries, observer) => {
        entries.forEach(entry => {
            if (entry.isIntersecting) {
                const img = entry.target;
                img.src = img.dataset.src;
                img.classList.add('loaded');
                observer.unobserve(img);
            }
        });
    });
    
    document.querySelectorAll('img[data-src]').forEach(img => {
        imageObserver.observe(img);
    });
}

// ===================================
// ACCESSIBILITY IMPROVEMENTS
// ===================================
// Add skip to content link
const skipLink = document.createElement('a');
skipLink.href = '#home';
skipLink.textContent = 'Skip to content';
skipLink.className = 'skip-link';
skipLink.style.cssText = `
    position: absolute;
    top: -40px;
    left: 0;
    background: #6366f1;
    color: white;
    padding: 8px;
    text-decoration: none;
    z-index: 100;
`;
document.body.prepend(skipLink);

skipLink.addEventListener('focus', () => {
    skipLink.style.top = '0';
});

skipLink.addEventListener('blur', () => {
    skipLink.style.top = '-40px';
});

// Keyboard navigation for sections
document.addEventListener('keydown', (e) => {
    const sections = ['home', 'about', 'skills', 'experience', 'projects', 'education', 'contact'];
    let currentIndex = -1;
    
    // Find current section
    sections.forEach((section, index) => {
        const element = document.getElementById(section);
        if (element) {
            const rect = element.getBoundingClientRect();
            if (rect.top <= 100 && rect.bottom >= 100) {
                currentIndex = index;
            }
        }
    });
    
    // Navigate with arrow keys
    if (e.key === 'ArrowDown' && currentIndex < sections.length - 1) {
        e.preventDefault();
        document.getElementById(sections[currentIndex + 1]).scrollIntoView({ behavior: 'smooth' });
    } else if (e.key === 'ArrowUp' && currentIndex > 0) {
        e.preventDefault();
        document.getElementById(sections[currentIndex - 1]).scrollIntoView({ behavior: 'smooth' });
    }
});

// ===================================
// INITIALIZATION
// ===================================

// Add ripple effect to all clickable elements
document.querySelectorAll('a, button, .btn, .nav-link, .social-link').forEach(element => {
    element.addEventListener('click', function(e) {
        const ripple = document.createElement('span');
        const rect = this.getBoundingClientRect();
        const size = Math.max(rect.width, rect.height);
        const x = e.clientX - rect.left - size / 2;
        const y = e.clientY - rect.top - size / 2;
        
        ripple.style.cssText = `
            position: absolute;
            width: ${size}px;
            height: ${size}px;
            border-radius: 50%;
            background: rgba(255, 255, 255, 0.6);
            top: ${y}px;
            left: ${x}px;
            pointer-events: none;
            animation: rippleEffect 0.6s ease-out;
        `;
        
        if (this.style.position !== 'absolute' && this.style.position !== 'relative') {
            this.style.position = 'relative';
        }
        if (!this.style.overflow) {
            this.style.overflow = 'hidden';
        }
        
        this.appendChild(ripple);
        setTimeout(() => ripple.remove(), 600);
    });
});

const rippleStyle = document.createElement('style');
rippleStyle.textContent = `
    @keyframes rippleEffect {
        0% {
            transform: scale(0);
            opacity: 1;
        }
        100% {
            transform: scale(4);
            opacity: 0;
        }
    }
`;
document.head.appendChild(rippleStyle);

// Create particle burst on button click
document.querySelectorAll('.btn').forEach(btn => {
    btn.addEventListener('click', (e) => {
        if (btn.textContent.includes('Hire Me')) {
            createConfetti(e.clientX, e.clientY);
        } else {
            createParticleBurst(e.clientX, e.clientY);
        }
    });
});

function createConfetti(x, y) {
    const colors = ['#6366f1', '#a855f7', '#ec4899', '#f59e0b', '#22c55e'];
    for (let i = 0; i < 30; i++) {
        const confetti = document.createElement('div');
        const color = colors[Math.floor(Math.random() * colors.length)];
        confetti.style.cssText = `
            position: fixed;
            width: ${Math.random() * 10 + 5}px;
            height: ${Math.random() * 10 + 5}px;
            background: ${color};
            pointer-events: none;
            z-index: 9999;
            left: ${x}px;
            top: ${y}px;
            border-radius: ${Math.random() > 0.5 ? '50%' : '0'};
        `;
        
        document.body.appendChild(confetti);
        
        const angle = (Math.PI * 2 * i) / 30;
        const velocity = Math.random() * 150 + 100;
        const vx = Math.cos(angle) * velocity;
        const vy = Math.sin(angle) * velocity - 50;
        
        let posX = 0, posY = 0, opacity = 1, rotation = 0;
        const gravity = 300;
        
        const animate = () => {
            posX += vx * 0.016;
            posY += (vy + gravity * 0.016) * 0.016;
            opacity -= 0.015;
            rotation += 5;
            
            confetti.style.transform = `translate(${posX}px, ${posY}px) rotate(${rotation}deg)`;
            confetti.style.opacity = opacity;
            
            if (opacity > 0) {
                requestAnimationFrame(animate);
            } else {
                confetti.remove();
            }
        };
        
        animate();
    }
}

function createParticleBurst(x, y) {
    for (let i = 0; i < 12; i++) {
        const particle = document.createElement('div');
        particle.style.cssText = `
            position: fixed;
            width: 8px;
            height: 8px;
            background: linear-gradient(135deg, #6366f1, #a855f7);
            border-radius: 50%;
            pointer-events: none;
            z-index: 9999;
            left: ${x}px;
            top: ${y}px;
        `;
        
        document.body.appendChild(particle);
        
        const angle = (Math.PI * 2 * i) / 12;
        const velocity = 100;
        const vx = Math.cos(angle) * velocity;
        const vy = Math.sin(angle) * velocity;
        
        let posX = 0, posY = 0, opacity = 1;
        
        const animate = () => {
            posX += vx * 0.016;
            posY += vy * 0.016;
            opacity -= 0.02;
            
            particle.style.transform = `translate(${posX}px, ${posY}px)`;
            particle.style.opacity = opacity;
            
            if (opacity > 0) {
                requestAnimationFrame(animate);
            } else {
                particle.remove();
            }
        };
        
        animate();
    }
}

console.log('✅ Portfolio initialized successfully!');

// Add success message hint
setTimeout(() => {
    console.log('%c💼 Ready to collaborate? Let\'s build something amazing together!', 'color: #22c55e; font-size: 16px; font-weight: bold;');
}, 1000);

// Simulate view counter
const views = Math.floor(Math.random() * 1000) + 500;
localStorage.setItem('portfolioViews', views);
console.log(`%c👀 Portfolio Views: ${views}`, 'color: #8b5cf6; font-size: 14px;');

// Close DOMContentLoaded wrapper
});
