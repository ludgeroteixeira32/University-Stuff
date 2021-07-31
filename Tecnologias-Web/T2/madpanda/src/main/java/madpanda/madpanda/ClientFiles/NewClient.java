package madpanda.madpanda.ClientFiles;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;

@Controller
public class NewClient {
    private static final Logger log = LoggerFactory.getLogger(NewClient.class);

    @Autowired
    private ClientRepository repository;

    @PostMapping("/new-client")
    public String newClient(
			@RequestParam(name="username", required=true, defaultValue="") String username, 
			@RequestParam(name="password", required=true, defaultValue="") String password,
			@RequestParam(name="role", required=true, defaultValue="") String role,
			Model model) 
    {
        
        String encodedPassword = new BCryptPasswordEncoder().encode(password);

        repository.save(new Client(username, encodedPassword, role));
        
        log.info("Users found with findAll():");
        log.info("-------------------------------");
        for (Client Client : repository.findAll()) {
            log.info(Client.toString());
        }
        log.info("");
        
        model.addAttribute("username", username);
        model.addAttribute("role", role);
        return "new-client-view";
    }
}