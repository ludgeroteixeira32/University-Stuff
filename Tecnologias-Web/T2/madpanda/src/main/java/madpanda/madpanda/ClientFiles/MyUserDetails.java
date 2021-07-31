package madpanda.madpanda.ClientFiles;

import java.util.Arrays;
import java.util.Collection;

import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.authority.SimpleGrantedAuthority;
import org.springframework.security.core.userdetails.UserDetails;
 
public class MyUserDetails implements UserDetails {
 
    private Client username;
     
    public MyUserDetails(Client username) {
        this.username = username;
    }
 
    @Override
    public Collection<? extends GrantedAuthority> getAuthorities() {
        SimpleGrantedAuthority authority = new SimpleGrantedAuthority(username.getRole());
        return Arrays.asList(authority);
    }
 
    @Override
    public String getPassword() {
        return username.getPassword();
    }
 
    @Override
    public String getUsername() {
        return username.getUsername();
    }
 
    @Override
    public boolean isAccountNonExpired() {
        return true;
    }
 
    @Override
    public boolean isAccountNonLocked() {
        return true;
    }
 
    @Override
    public boolean isCredentialsNonExpired() {
        return true;
    }
 
    @Override
    public boolean isEnabled() {
        return true;
    }
    
}